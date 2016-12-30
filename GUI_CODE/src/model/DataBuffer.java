/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

public class DataBuffer {
    
    public static byte[] readBuffer;
    public static int validBytes;
    
    public static void initialize(int size){
        readBuffer = new byte[size];
    }
    
    public static boolean read(int size, byte[] inputBuffer)
    {
        validBytes = size;
        if(size > 0){
            for(int i = 0; i < size; i++)
                readBuffer[i] = inputBuffer[i];
            return true;
        }
        return false;
    }
}
