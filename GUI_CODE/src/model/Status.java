/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.awt.Color;
import java.util.ArrayList;

public class Status {
    public static boolean updated;
    public static ArrayList<Module> module;
    public static boolean transmit;
    public static boolean commLink;
    public static int mode;
    public static int masterState;	
    public static Color red = new Color(180,100,100);
    public static Color green = new Color(50,225,100);
    public static Color skyblue = new Color(100,150,180);
    public static Color lightYellow = new Color(200,200,100);
    public static Color darkGray = new Color(169,169,169);
    public static int NO_MODULE = 0;
    public static int LED_MODULE = 1;
    public static int SOUND_MODULE = 2;
    public static int LCD_MODULE = 4;

    public static void initialize(){
        updated = false;
        module = new ArrayList<Module>(3);
        module.add(new Module());
        module.add(new Module());
        module.add(new Module());
        transmit = false;
    }
    //Called every time data is received by CommDirector
    public static boolean updateAll(byte[] readBuffer){
    	if(readBuffer.length >= 8){
    		masterState = (readBuffer[0] & 0xF0) >> 4;
    		module.get(0).active = (readBuffer[1] & 0x01) == 1;
    		module.get(1).active = ((readBuffer[1] & 0x02) >> 1) == 1;
    		module.get(2).active = ((readBuffer[1] & 0x04) >> 2) == 1;
    		module.get(0).update(readBuffer[6], readBuffer[7]);
    		module.get(1).update(readBuffer[4], readBuffer[5]);
    		module.get(2).update(readBuffer[2], readBuffer[3]);
    		return true;
    	}
    	return false;
    }
    
    public static int getEnabledParameter(){
		int enableResult = 0;
		if(module.get(0).enabled) enableResult = enableResult + 1;
		if(module.get(1).enabled) enableResult = enableResult + 2;
		if(module.get(2).enabled) enableResult = enableResult + 4;
		return enableResult;
    }
    
    public static void simCommandUpdate(byte command){
        module.get(0).enabled = true;
        module.get(0).command= (int) command;
        module.get(1).enabled = true;
        module.get(1).command = (int) command;
        module.get(2).enabled = true;
        module.get(2).command = (int) command;
    }
    
}
