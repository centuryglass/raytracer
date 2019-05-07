/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package raytracergui;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

/**
 *
 * @author Anthony
 */
public class RaytracerGUI extends Application {
    
    @Override
    public void start(Stage primaryStage) {
        MainWindow mainWin = new MainWindow();
        mainWin.setVisible(true);
    }

    /**
     * The main() method is ignored in correctly deployed JavaFX application.
     * main() serves only as fallback in case the application can not be
     * launched through deployment artifacts, e.g., in IDEs with limited FX
     * support. NetBeans ignores main().
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
}
