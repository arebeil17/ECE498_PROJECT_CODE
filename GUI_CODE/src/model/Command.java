/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

public class Command {
    private boolean update;

    public int mode;
    public int priority;
    public int select;
    public int config;
    public char command;
    public byte[] dataPacket;

    public static int NORMAL = 2;
    public static int CRITICAL = 3;
    public static int NONE = 0;

    public Command(){
            dataPacket = new byte[3];
            update = false;
            priority =  NORMAL;
            dataPacket[0] = 0;
            dataPacket[1] = 0;
            dataPacket[2] = 0;
    }

    public void updateDataPacket(byte control, byte config, byte command){

            dataPacket[0] = control;
            dataPacket[1] = config;
            dataPacket[2] = command;

            mode =	       (control & 0xF0) >> 4;
            priority =     (control & 0x0F);
            select =       (config & 0xF0) >> 4;
            this.config =  (config & 0x0F);
            this.command = (char) command;
    }

    public void setCommandData(){
            mode =	       (dataPacket[0] & 0xF0) >> 4;
            priority =     (dataPacket[0] & 0x0F);
            select =       (dataPacket[1] & 0xF0) >> 4;
            config = 	   (dataPacket[1] & 0x0F);
            command =      (char) dataPacket[2];
    }

    public boolean isUpdate() {
            return update;
    }

    public void setUpdate(boolean update) {
            this.update = update;
    }
}
