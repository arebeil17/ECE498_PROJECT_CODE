/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Driver;

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
import com.pi4j.util.CommandArgumentParser;
import com.pi4j.util.Console;
import java.io.IOException;

public class CommTest2 {
    
       public char[] reply = new char[2];
       // create an instance of the serial communications class
       Serial serial = SerialFactory.createInstance();
    
       boolean ready = false;
   
       public static void main(String[] args) throws InterruptedException, IOException {
        
        CommTest2 commTest = new CommTest2();

        // create Pi4J console wrapper/helper
        // (This is a utility class to abstract some of the boilerplate code)
        final Console console = new Console();

        // print program title/header
        console.title("<-- The Pi4J Project -->", "Serial Communication Example");

        // allow for user to exit program using CTRL-C
        console.promptForExit();

        // create and register the serial data listener
        commTest.serial.addListener(new SerialDataEventListener() {
            @Override
            public void dataReceived(SerialDataEvent event) {
                // NOTE! - It is extremely important to read the data received from the
                // serial port.  If it does not get read from the receive buffer, the
                // buffer will continue to grow and consume memory.
                // print out the data received to the console
                try {
                    commTest.readBuffer(event.getBytes());
                    System.out.println("\nReceiving Data... [HEX DATA] :" + event.getHexByteString() + " [BYTE DATA] :" + commTest.reply[0] + commTest.reply[1]
                                       +" [ASCII DATA]:" + event.getAsciiString());
                    commTest.ready = true;
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
            console.box(" Connecting to: " + config.toString(),
                    " We are sending ASCII data on the serial port every 1 second.",
                   " Data received on serial port will be displayed below.");


            // open the default serial device/port with the configuration settings
            commTest.serial.open(config);
            
            int i = 0;
            int k = 0;
            byte[] command = new byte[3];
            // continuous loop to keep the program running until the user terminates the program
            while(console.isRunning()) {
                
                if(i < 8) i++;
                else i = 4;
           
                try {
                    command[0] = (byte) i;
                    command[1] = (byte) i;
                    command[2] = (byte) i;
                    // write a formatted string to the serial transmit buffer
                    //serial.write("CURRENT TIME: " + new Date().toString());
                    if(commTest.ready) {
                        System.out.println("Transmitting Data... Sent: "+ command[0] + command[1] + command[2]);
                        commTest.serial.write(command);
                        commTest.ready = false;
                    }else{
                        System.out.println("\nWaiting for Arduino Mega reply...");
                        System.out.println("Transmitting Data...  Sent: "+ command[0] + command[1] + command[2]);
                        commTest.serial.write(command);
                        Thread.sleep(5000);
                    }

                    // write a simple string to the serial transmit buffer
                    //serial.write("Second Line");

                    // write a individual characters to the serial transmit buffer
                    //serial.write('\r');
                    //serial.write('\n');

                    // write a string terminating with CR+LF to the serial transmit buffer
                    //serial.writeln("Third Line");
                }
                catch(IllegalStateException ex){
                    ex.printStackTrace();
                }
                Thread.sleep(250);
            }

        }
        catch(IOException ex) {
            System.out.println(" ==>> SERIAL SETUP FAILED : " + ex.getMessage());
            return;
        }
    }
    public void readBuffer(byte[] buffer){
        reply[0] = (char) buffer[0];
        reply[1] = (char) buffer[1];
        
    }
    
}
