/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

public class Status {
    public static boolean updated;
    public static int mode;
    public static int priority;
    public static int select;
    public static int config;
    public static byte command;
    public static boolean transmit;
    public static boolean commLink;

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
