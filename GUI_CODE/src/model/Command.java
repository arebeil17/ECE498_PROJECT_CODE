/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.ArrayList;

public class Command {
    private boolean update;

    public int mode;
    public int priority;
    public int select;
    public int config;
    public char command;
    public ArrayList<Integer> abort;
    public byte[] dataPacket;
    public static byte START_BYTE = (byte) 0xCC;
    public static int NORMAL = 2;
    public static int CRITICAL = 3;
    public static int NONE = 0;
    public static int NO_COMMAND = 0;
    public static int ABORT = 4;
    public static int SLEEP = 2;

    public Command(){
            dataPacket = new byte[8];
            update = false;
            priority =  NORMAL;
            dataPacket[0] = START_BYTE;
            abort = new ArrayList<Integer>(3); 
            for(int i = 1; i < 8; i++) dataPacket[i] = 0;
    }

    public void updateDataPacket(byte control, byte config, byte command){
            dataPacket[0] = control;
            dataPacket[1] = config;
            dataPacket[2] = command;

            mode =	   (control & 0xF0) >> 4;
            priority =     (control & 0x0F);
            select =       (config & 0xF0) >> 4;
            this.config =  (config & 0x0F);
            this.command = (char) command;
    }
    //Update command dataPacket with control
    //Simultaneous input makes all submodule flags, and commands the same
    public void simultInputUpdate(byte control, byte flag, byte command){
            dataPacket[1] = control;
            for(int i = 2; i < 8; i = i + 2){
                    dataPacket[i] = (byte)(0x10 | (flag & 0x0F));
                    dataPacket[i+1] = command;
            }
            Status.simCommandUpdate(command);
    }
    public void independentInputUpdate()
    {
    	//Update MasterControl data
        dataPacket[1] = (byte) ((Status.mode << 4) | (Status.getEnabledParameter()));
        //---------------------------------------------------------------------------
        //Update Module 3 command data packet
        dataPacket[2] = (byte) ((Status.mode << 4) | abort.get(2));
        if(Status.module.get(2).enabled) dataPacket[3] = Status.module.get(2).command.byteValue();
        else dataPacket[3] = (byte) NO_COMMAND;
       //---------------------------------------------------------------------------
        //Update Module 2 command data packet
        dataPacket[4] = (byte) ((Status.mode << 4) | abort.get(1));
        if(Status.module.get(1).enabled) dataPacket[5] = Status.module.get(1).command.byteValue();
        else dataPacket[5] = (byte) NO_COMMAND;
       //---------------------------------------------------------------------------
        //Update Module 1 command data packet
        dataPacket[6] = (byte) ((Status.mode << 4) | abort.get(0));
        if(Status.module.get(0).enabled) dataPacket[7] = Status.module.get(0).command.byteValue();
        else dataPacket[7] = (byte) NO_COMMAND;

    }

    public void setCommandData(){
            mode =	   (dataPacket[0] & 0xF0) >> 4;
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
