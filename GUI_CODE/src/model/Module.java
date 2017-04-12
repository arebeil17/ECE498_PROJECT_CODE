package model;

public class Module {
	
	public boolean active;
	public boolean enabled;
        public Integer abort;
	public Integer state;
	public Integer mode;
	public Integer config;
	public Integer command;        //Command to be sent
	public Integer currentCommand; //Command module is currently executing
	
	public Module(){
		active = false;
		enabled = false;
                abort = 0;
		state = new Integer(0);
		mode = new Integer(0);
		config = new Integer(Status.NO_MODULE);
		command = new Integer(Command.NO_COMMAND);
		currentCommand = new Integer(Command.NO_COMMAND);
	}
	
	public void update(byte status, byte command){
		state = status & (0xF0) >> 4;
		config = status & (0x07);
		currentCommand = (int) command;
	}
	
	public String idString(){
		if(config == Status.LED_MODULE) return "LED Module";
		else if(config == Status.SOUND_MODULE) return "Sound Module";
		else if(config == Status.LCD_MODULE) return "LCD Module";
		else return "No Module";
	}
	
}
