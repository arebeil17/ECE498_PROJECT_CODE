/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import com.pi4j.io.serial.*;
import java.io.IOException;

/**
 *
 * @author pi
 */
public class CommDirector {
    public Command command;
    public Reply reply;
    public Serial serial = SerialFactory.createInstance();
    public static byte START_BYTE = (byte) 0xCC;
    
    public CommDirector(){
        command = new Command();
        reply   = new Reply();
         // create and register the serial data listener
        serial.addListener(new SerialDataEventListener() {
            @Override
            public void dataReceived(SerialDataEvent event) {
                // NOTE! - It is extremely important to read the data received from the
                // serial port.  If it does not get read from the receive buffer, the
                // buffer will continue to grow and consume memory.
                // print out the data received to the console
                try {
                    DataBuffer.read(event.getBytes().length, event.getBytes());
                        System.out.println("\nReceiving Data... [HEX DATA] :" 
                                           + event.getHexByteString() + " [BYTE DATA] :" 
                                           //+ DataBuffer.readBuffer[0] 
                                           +" " +DataBuffer.readBuffer[1]
                                           //+ DataBuffer.readBuffer[2] 
                                           //+ DataBuffer.readBuffer[3] 
                                           //+ DataBuffer.readBuffer[4] 
                                           //+ DataBuffer.readBuffer[5]
                                           +" " +DataBuffer.readBuffer[6] 
                                           +" " +DataBuffer.readBuffer[7] 
                                           +" [ASCII DATA]:" + event.getAsciiString());
                        if(!recieve()) //recieve data stored in dataBuffer
                            System.out.println("Recieved insufficient or corrupted data.");
                    
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        try {
            // create serial config object
            SerialConfig config = new SerialConfig();

            // set default serial settings (device, baud rate, flow control, etc)
            //
            // by default, use the DEFAULT com port on the Raspberry Pi (exposed on GPIO header)
            // NOTE: this utility method will determine the default serial port for the
            //       detected platform and board/model.  For all Raspberry Pi models
            //       except the 3B, it will return "/dev/ttyAMA0".  For Raspberry Pi
            //       model 3B may return "/dev/ttyS0" or "/dev/ttyAMA0" depending on
            //       environment configuration.
            config.device("/dev/ttyACM0")
            //config.device(SerialPort.getDefaultPort())
                  .baud(Baud._38400)
                  .dataBits(DataBits._8)
                  .parity(Parity.NONE)
                  .stopBits(StopBits._1)
                  .flowControl(FlowControl.NONE);

            // display connection details
            System.out.println(" Connecting to: " + config.toString() +
                    " \nWe are sending ASCII data on the serial port every 1 second."+
                   " \nData received on serial port will be displayed below.");

            // open the default serial device/port with the configuration settings
            serial.open(config);
            Status.commLink = true; //Communication successfully established
                                    //set flag true
            
        }
        catch(IOException ex) {
            System.out.println(" ==>> SERIAL SETUP FAILED : " + ex.getMessage());
            Status.commLink = false;
            return;
        }
    }

    public boolean transmit(){
        try{
            System.out.println("Transmitting Data... Sent: "+ (byte) command.dataPacket[1]
                                                            +", [" +(byte) command.dataPacket[2]
                                                            +" " +(byte) command.dataPacket[3]
                                                            +"], [" +(byte) command.dataPacket[4]
                                                            +" " +(byte) command.dataPacket[5]
                                                            +"], [" +(byte) command.dataPacket[6]
                                                            +" " +(byte) command.dataPacket[7] +"]");
            serial.write(command.dataPacket);
        }
        catch(IOException ex){
                    ex.printStackTrace();
        }
        Status.transmit = false; // reset transmit flag
        return true;
    }

    public boolean recieve(){
        if(DataBuffer.validBytes >= 7){
            System.out.println("Reply Confirmed...");
            if(DataBuffer.readBuffer[0] != START_BYTE) return false;
            reply.setDataPacket(DataBuffer.readBuffer);
            Status.updateAll(DataBuffer.readBuffer); //Update all tracked status data
            return true;
        }
        return false;
    }
}
