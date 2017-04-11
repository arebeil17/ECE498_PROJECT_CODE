/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package driver;

import com.pi4j.io.serial.Baud;
import com.pi4j.io.serial.DataBits;
import com.pi4j.io.serial.FlowControl;
import com.pi4j.io.serial.Parity;
import com.pi4j.io.serial.Serial;
import com.pi4j.io.serial.SerialConfig;
import com.pi4j.io.serial.SerialDataEvent;
import com.pi4j.io.serial.SerialDataEventListener;
import com.pi4j.io.serial.SerialFactory;
import com.pi4j.io.serial.StopBits;
import com.pi4j.util.Console;
import java.awt.EventQueue;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import model.CommDirector;
import model.DataBuffer;
import model.Status;
import view.MPB_GUI;

/**
 *
 * @author pi
 */
public class MPB_Driver {
   
    public boolean running = false;
    // create an instance of the serial communications class
   
    boolean ready = false;
    
    public static void main(String[] args )throws InterruptedException{
    	Status.initialize();
        DataBuffer.initialize(64);
        boolean running = true;
        MPB_GUI mpb_GUI = new MPB_GUI();
        mpb_GUI.setVisible(true);
        CommDirector commDirector = new CommDirector();
   

        mpb_GUI.simPanel.btnSend.addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent arg0) {
                        commDirector.command.simultInputUpdate((byte) 0x11,
                                                               (byte) 0x00,
                                                               (byte) mpb_GUI.simPanel.checkButtons());
                        Status.transmit = true;
                }
        });
        mpb_GUI.independentPanel.btnSend.addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent arg0) {
                    commDirector.command.independentInputUpdate();
                    Status.transmit = true;
                }
        });
        //Check whether serial communication is working
        if(Status.commLink){
            while(running) {
                if(Status.transmit){
                    System.out.println("\nTransmit Started:");
                    commDirector.transmit();
                }
                Thread.sleep(100);
            }
        }else{
            System.out.println("\nCommunication Link failed.");
        }
    }
    
}
