/*Main Ray tracer program
 *Anthony Brown
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <set>
#include <map>


#include <vector>
#include <limits>
#include <functional>
using namespace std;


#include <boost/thread.hpp>
#include <boost/thread/pthread/mutex.hpp>
#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Vector3D.h"
#include "Random.h"
#include "XMLSceneParser.h"
#include <boost/filesystem.hpp>

#include "Ray.h"
#include "Scene.h"
#include "Light.h"
#include "XMLContainerClass.h"
#include "Timer.h"
#include "Camera.h"
#include "Shape.h"
#include "Shader.h"
using namespace sivelab;
 
#include "LightMap.h"

class threadData {
public:

    threadData() {
        percentComplete = 0;
        lastPrinted = 0;
        nRays = 100;
        resX = 100;
        resY = 100;
        imData = new png::image< png::rgb_pixel >(resX, resY);
        nCPUs = boost::thread::hardware_concurrency();
        outputName = "render.png";
        sectionCount = 25;
        sectionsCompleted = 0;
        generatePhotonMap = false;
    }
    map<int, bool> sectionTaken;
    string outputName;
    int nCPUs;
    int nRays;
    int sectionCount;
    int sectionsCompleted;
    Camera * cam;
    Scene * scene;
    int resX, resY;
    png::image< png::rgb_pixel > * imData;
    boost::mutex workMutex;
    float percentComplete;
    int lastPrinted;
    bool generatePhotonMap;
private:
};

class renderWorkThread {
public:

    renderWorkThread(threadData * td_ptr)

    : m_threadDataPtr(td_ptr) {
    }

    void operator()() {
        Random * rand = new Random();
        threadData * tData = m_threadDataPtr;
        while (tData->sectionsCompleted < tData->sectionCount) {
            int section = -1;
            tData->workMutex.lock();
            for (int i = 0; i < tData->sectionCount; i++) {
                if (section == -1 && !tData->sectionTaken[i]) {
                    tData->sectionTaken[i] = true;
                    section = i;
                    //cout << "Section " << i + 1 << " of " << tData->sectionCount
                    //      << " claimed\n";
                }
            }
            if (section == 0) {
                try {
                    tData->imData->write(tData->outputName);
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
            }

            tData->workMutex.unlock();

            if (section != -1) {
                int XBegin = section;
                for (int y = 0; y < tData->imData->get_height(); y++) {
                    for (int x = XBegin; x < tData->imData->get_width(); x = x + tData->sectionCount) {
                        Vector3D hitCol;
                        Ray r;
                        r.setRand(rand);
                        r.setMaxRayNum(tData->nRays);
                        for (int i = 0; i < tData->nRays; i++) {
                            r.setRayNum(i);
                            tData->cam->computeRay(x, y, r);
                            HitStruct hit;
                            float tmin = 0;
                            float tmax = 99999;
                            bool intersect =
                                    tData->scene->intersect(r, tmin, tmax, hit);


                            if (intersect) {
                                hitCol += hit.getHitColor(tData->scene)*255 * (1.0 / tData->nRays);
                                r.setPhoton(hit.getViewingRay().getPhoton());

                            } else {
                                hitCol += tData->scene->getSceneColor()*255 * (1.0 / tData->nRays);
                            }
                        }
                        //tData->workMutex.lock();
                        (*tData->imData)[y][x] =
                                png::rgb_pixel(hitCol[0], hitCol[1], hitCol[2]);
                        //tData->workMutex.unlock();
                    }
                    tData->workMutex.lock();
                    tData->percentComplete +=
                            ((100.0 / tData->resY) / tData->sectionCount);
                    if (tData->percentComplete > (tData->lastPrinted + 1)) {
                        tData->lastPrinted = (int) tData->percentComplete;
                        cout << tData->lastPrinted << " percent complete.\n";

                    }
                    tData->workMutex.unlock();
                    XBegin = (XBegin + (tData->sectionCount / 5)) % tData->sectionCount;

                }
                tData->workMutex.lock();
                try {
                    tData->imData->write(tData->outputName);
                } catch (exception& e) {
                }//incremental image write
                //failed, but we don't need to do anything about it
                tData->sectionsCompleted++;
                tData->workMutex.unlock();
            }
        }
        tData->workMutex.lock();
        try {
            tData->imData->write(tData->outputName);
        } catch (exception& e) {
            cout << e.what() << endl;
        }
        tData->workMutex.unlock();
        delete rand;
    }

private:
    threadData *m_threadDataPtr;
};

void processScene(string fName, threadData * tData) {
    XMLContainerClass cont;
    XMLSceneParser xmlScene;
    // register object creation function with xmlScene

    xmlScene.registerCallback("sceneParameters", &cont);
    xmlScene.registerCallback("camera", &cont);
    xmlScene.registerCallback("light", &cont);
    xmlScene.registerCallback("texture", &cont);
    xmlScene.registerCallback("shader", &cont);
    xmlScene.registerCallback("instance", &cont);
    xmlScene.registerCallback("shape", &cont);

    xmlScene.parseFile(fName);
    tData->cam = cont.getCamera();
    (tData->cam)->setResolution(tData->resX, tData->resY);
    tData->imData->resize(tData->resX, tData->resY);
    tData->scene = cont.getScene();
    tData->scene->setCamera(tData->cam);
    tData->scene->generatePhotonMap = tData->generatePhotonMap;
    cout << "Building shape tree acceleration structure\n";
    tData->scene->buildShapeTree();
    cout << "Shape tree built\n";
}

int main(int argc, char *argv[]) {
    threadData * tData = new threadData;
    GraphicsArgs args;
    args.process(argc, argv);
    if (args.inputFileName != "") {
        if (args.outputFileName != "") tData->outputName = args.outputFileName;
        else tData->outputName = args.inputFileName + ".png";
        tData->resX = args.width;
        tData->resY = args.height;
        tData->nRays = args.rpp;

        processScene(args.inputFileName, tData);
        if(args.depthOfFieldDistance != 0)
            tData->cam->setDepthOfField(args.depthOfFieldDistance);

        Timer t;
        Timer_t start = t.tic();



        for (unsigned int i = 0; i < tData->nCPUs; i++) {
            tData->sectionTaken[i] = false;
        }
        std::vector<boost::thread*> activatedThreads(tData->nCPUs);
        for (unsigned int i = 0; i < tData->nCPUs; i++) {
            renderWorkThread rwt(tData);
            activatedThreads[i] = new boost::thread(rwt);
        }

        for (unsigned int i = 0; i < tData->nCPUs; i++) {
            activatedThreads[i]->join();
        }

        bool printed = false;
        while (!printed) {
            try {
                tData->imData->write(tData->outputName);
                printed = true;
            } catch (exception& e) {
                printed = false;
            }
        }

        Timer_t end = t.tic();
        Timer_t duration = t.deltas(start, end);
        cout << "Rendered in " << (duration / 60)
                << "minutes, " << (duration % 60) << "seconds.\n";

    } else {
        cout << "Rendering all scenes in sceneFiles directory\n";
        cout << "Enter desired resolution.\nx:";
        cin >> tData->resX;
        cout << "y:";
        cin >> tData->resY;
        cout << "Ray count:";
        cin >> tData->nRays;
        cout<<"Use Photon map?(y/n)";
        char c;
        cin>>c;
        if(c == 'y') tData->generatePhotonMap = true;
         
        while (sqrt(tData->nRays) != (int) sqrt(tData->nRays)) {
            tData->nRays++;
        }
        tData->imData->resize(tData->resX, tData->resY);
        namespace fs = boost::filesystem;
        fs::path sceneFiles("./sceneFiles");
        fs::directory_iterator end_iter;

        if (fs::exists(sceneFiles)
                && fs::is_directory(sceneFiles)) {
            for (fs::directory_iterator dir_iter(sceneFiles);
                    dir_iter != end_iter; ++dir_iter) {
                if (fs::is_regular_file(dir_iter->status())) {
                    string filename = (dir_iter->path()).string();
                    if (filename.substr(filename.find_last_of('.')) == ".xml") {
                        cout << "Processing " << filename << "\n";
                        processScene(filename, tData);
                        tData->cam->setResolution(tData->resX, tData->resY);

                        cout << "Rendering " <<
                                (dir_iter->path()).string() << "\n";
                        Timer t;
                        Timer_t start = t.tic();
                        tData->outputName = (dir_iter->path()).string() + ".png";

                        for (unsigned int i = 0; i < tData->nCPUs; i++) {
                            tData->sectionTaken[i] = false;
                        }
                        std::vector<boost::thread*> activatedThreads
                                (tData->nCPUs);
                        for (unsigned int i = 0; i < tData->nCPUs; i++) {
                            renderWorkThread rwt(tData);
                            activatedThreads[i] = new boost::thread(rwt);
                        }

                        for (unsigned int i = 0; i < tData->nCPUs; i++) {
                            activatedThreads[i]->join();
                        }
                        bool printed = false;
                        while (!printed) {
                            try {
                                tData->imData->write(tData->outputName);
                                printed = true;
                            } catch (exception& e) {
                                printed = false;
                            }
                        }

                        tData->percentComplete = 0;
                        tData->lastPrinted = 0;
                        tData->sectionTaken.clear();
                        tData->sectionsCompleted = 0;
                        delete tData->imData;
                        tData->imData = new png::image< png::rgb_pixel >(tData->resX, tData->resY);

                        Timer_t end = t.tic();
                        Timer_t duration = t.deltas(start, end);
                        cout << "Rendered in " << duration / 60
                                << " minute(s), " << (duration % 60)
                                << "second(s).\n";
                    }
                }
            }
        }
    }

    exit(EXIT_SUCCESS);
}



