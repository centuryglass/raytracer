/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package raytracergui;

import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;

/**
 *
 * @author Anthony
 */
public class MainWindow extends javax.swing.JFrame implements WindowListener {

    /**
     * Creates new form NewJFrame
     */
    public MainWindow() {
        initComponents();
        file = new FileSelect();
        file.addWindowListener(this);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jTextField4 = new javax.swing.JTextField();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenu2 = new javax.swing.JMenu();
        inputFile = new javax.swing.JButton();
        outputFile = new javax.swing.JTextField();
        label1 = new java.awt.Label();
        label2 = new java.awt.Label();
        resX = new javax.swing.JTextField();
        resY = new javax.swing.JTextField();
        label3 = new java.awt.Label();
        raysPerPixel = new javax.swing.JTextField();
        renderButton = new javax.swing.JButton();
        inputLabel = new java.awt.Label();
        jScrollPane1 = new javax.swing.JScrollPane();
        outputText = new javax.swing.JTextPane();
        jMenuBar2 = new javax.swing.JMenuBar();
        menu = new javax.swing.JMenu();
        rayTracerSelect = new javax.swing.JMenuItem();

        jTextField4.setText("jTextField4");

        jMenu1.setText("File");
        jMenuBar1.add(jMenu1);

        jMenu2.setText("Edit");
        jMenuBar1.add(jMenu2);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Raytracer");

        inputFile.setText("Select Input File");
        inputFile.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                inputFileActionPerformed(evt);
            }
        });

        outputFile.setText("rendered image");
        outputFile.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                outputFileActionPerformed(evt);
            }
        });

        label1.setText("Output File Name:");

        label2.setText("Resolution");

        resX.setText("500");

        resY.setText("500");

        label3.setText("Rays per pixel:");

        raysPerPixel.setText("4");

        renderButton.setText("Render");
        renderButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                renderButtonActionPerformed(evt);
            }
        });

        inputLabel.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        inputLabel.setText("Scene: ");

        jScrollPane1.setViewportView(outputText);

        menu.setText("File");

        rayTracerSelect.setText("Select RayTracer.exe");
        rayTracerSelect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                rayTracerSelectActionPerformed(evt);
            }
        });
        menu.add(rayTracerSelect);

        jMenuBar2.add(menu);

        setJMenuBar(jMenuBar2);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 470, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(inputLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 466, Short.MAX_VALUE)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(label1, javax.swing.GroupLayout.PREFERRED_SIZE, 191, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(resX, javax.swing.GroupLayout.PREFERRED_SIZE, 84, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(18, 18, 18)
                                        .addComponent(resY, javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(label3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(92, 92, 92)
                                        .addComponent(raysPerPixel, javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                .addGap(0, 0, Short.MAX_VALUE)))
                        .addGap(20, 20, 20))
                    .addComponent(outputFile))
                .addContainerGap())
            .addGroup(layout.createSequentialGroup()
                .addGap(29, 29, 29)
                .addComponent(inputFile, javax.swing.GroupLayout.PREFERRED_SIZE, 191, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(renderButton, javax.swing.GroupLayout.PREFERRED_SIZE, 191, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap(21, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(inputFile)
                    .addComponent(renderButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(inputLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(label1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(outputFile, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(resX, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(resY, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(label3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(raysPerPixel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(26, 26, 26)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    public void windowClosed(WindowEvent e) {
        raytracer = file.getRayTracerPath();
        sceneFile = file.getSceneFilePath();
        inputLabel.setText("scene: " + sceneFile);
    }

    public void windowClosing(WindowEvent e) {
    }

    public void windowOpened(WindowEvent e) {
    }

    public void windowIconified(WindowEvent e) {
    }

    public void windowDeiconified(WindowEvent e) {
    }

    public void windowActivated(WindowEvent e) {
    }

    public void windowDeactivated(WindowEvent e) {
    }

    public void windowGainedFocus(WindowEvent e) {
    }

    public void windowLostFocus(WindowEvent e) {
        raytracer = file.getRayTracerPath();
        sceneFile = file.getSceneFilePath();
        inputLabel.setText("scene: " + sceneFile);
    }

    public void windowStateChanged(WindowEvent e) {
        raytracer = file.getRayTracerPath();
        sceneFile = file.getSceneFilePath();
        inputLabel.setText("scene: " + sceneFile);
    }

    private void rayTracerSelectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_rayTracerSelectActionPerformed
        file.setFileType("r");
        file.setAlwaysOnTop(true);
        file.setVisible(true);
    }//GEN-LAST:event_rayTracerSelectActionPerformed

    private void inputFileActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_inputFileActionPerformed
        file.setFileType("s");
        file.setAlwaysOnTop(true);
        file.setVisible(true);
    }//GEN-LAST:event_inputFileActionPerformed

    private void outputFileActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_outputFileActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_outputFileActionPerformed

    private void renderButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_renderButtonActionPerformed
        raytracer = file.getRayTracerPath();
        sceneFile = file.getSceneFilePath();
        String command = "";
        boolean correct = true;
        if (raytracer.equals("")) {
            JOptionPane.showMessageDialog(this, "Please select the ray tracer location");
            correct = false;
        } else {
            command = command + (raytracer + " ");
        }
        if (sceneFile.equals("")) {
            JOptionPane.showMessageDialog(this, "Please select an xml scene to render");
            correct = false;
        } else {
            command = command + ("-i \"" + sceneFile + "\" ");
        }

        if (outputFile.getText().equals("")) {
            JOptionPane.showMessageDialog(this, "Please specify an output file name");
            correct = false;
        } else {
            command = command + ("-o \"" + outputFile.getText() + ".png\" ");
        }
        if (resX.getText().equals("") || resY.getText().equals("")) {
            JOptionPane.showMessageDialog(this, "Please specify an image resolution");
            correct = false;
        } else {
            command = command + ("-w " + resX.getText() + " -h " + resY.getText() + " ");
        }
        if (raysPerPixel.getText().equals("")) {
            JOptionPane.showMessageDialog(this, "Please specify the number of rays per pixel");
            correct = false;
        } else {
            command = command + ("-r " + raysPerPixel.getText());
        }
        if (correct) {
            Runtime rt = Runtime.getRuntime();
            Process p;
            BufferedReader stdInput;
            String s;
            try {
                p = rt.exec(command);
                stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
                while ((s = stdInput.readLine()) != null) {
                    outputText.setText(s);
                }
            } catch (IOException ex) {
                Logger.getLogger(MainWindow.class.getName()).log(Level.SEVERE, null, ex);
            }
        }


    }//GEN-LAST:event_renderButtonActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainWindow().setVisible(true);
            }
        });
    }
    private FileSelect file;
    private String raytracer;
    private String sceneFile;
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton inputFile;
    private java.awt.Label inputLabel;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuBar jMenuBar2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextField jTextField4;
    private java.awt.Label label1;
    private java.awt.Label label2;
    private java.awt.Label label3;
    private javax.swing.JMenu menu;
    private javax.swing.JTextField outputFile;
    private javax.swing.JTextPane outputText;
    private javax.swing.JMenuItem rayTracerSelect;
    private javax.swing.JTextField raysPerPixel;
    private javax.swing.JButton renderButton;
    private javax.swing.JTextField resX;
    private javax.swing.JTextField resY;
    // End of variables declaration//GEN-END:variables
}
