/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.awt.Color;

public class Status {
    public static boolean updated;
    public static int mode;
    public static int priority;
    public static int select;
    public static int config;
    public static byte command;
    public static boolean transmit;
    public static boolean commLink;
    
    public static Color red = new Color(180,100,100);
    public static Color green = new Color(50,225,100);
    public static Color skyblue = new Color(100,150,180);
    public static Color lightYellow = new Color(200,200,100);
    public static Color darkGray = new Color(169,169,169);

    public static void initialize(){
        updated = false;
        mode = 0;
        priority = 0;
        select = 0;
        config = 0;
        command = 0;
        transmit = false;
    }

    public static byte getControlData(){
        byte control = 0;
        control = (byte) (((mode & 0x0F) << 4) | (priority & 0x0F));
        return control;
    }

    public static byte getConfigData(){
        byte config = 0;
        config = (byte) (((select & 0x0F) << 4) | (Status.config & 0x0F));
        return config;
    }

    public static byte getCommandData(){
        return command;
    }
}
