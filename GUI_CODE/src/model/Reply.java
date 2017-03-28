/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author pi
 */
public class Reply {
    public int status;
    public int mode;
    public int confirmation;

    public int activeSlots;
    public int config1;
    public int config2;
    public int config3;
    public static byte START_BYTE = (byte) 0xCC;
    public byte[] dataPacket;

    public Reply(){

        status = 0;
        mode = 0;
        confirmation = 0;

        activeSlots = 0;
        config1 = 0;
        config2 = 0;
        config3 = 0;

        dataPacket = new byte[7];
        //dataPacket[0] = START_BYTE;
    }

    public void updateDataPacket()
    {
        dataPacket[0] = (byte) ((status << 4) | (mode << 3) | (confirmation));
        dataPacket[1] = (byte) ((activeSlots << 6) | (config1 << 4) | (config2 << 2) | (config3));
    }

    public void setDataPacket(byte[] newPacket)
    {
        System.arraycopy(newPacket, 0, dataPacket, 0, 7);
    }

    public void setDataPacket(byte status, byte config) 
    {
        this.status = (status & 0xF0) >> 4;
        this.mode = (status & 0x04) >> 3;
        this.confirmation = (status & 0x07);
        this.activeSlots = (config & 0xC0) >> 6;
        this.config1 = (config & 0x30) >> 4;
        this.config2 = (config & 0x0C) >> 2;
        this.config3 = (config & 0x03);
        dataPacket[0] = status;
        dataPacket[1] = config;
    }
}
