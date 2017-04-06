package view;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.util.ArrayList;

import javax.swing.ButtonGroup;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.border.LineBorder;

import model.Status;

import javax.swing.JComboBox;

public class SimPanel extends JPanel {
	
	public ArrayList<JTextField> simPayloadStatus;
    //public ArrayList<JRadioButton> functionBtn;
    public ButtonGroup simBtnGroup = new ButtonGroup();
    public JComboBox comboBox;
    public JButton btnSend;
    public JButton btnAbort;
    public JTextField textField;
	/**
	 * Create the panel.
	 */
	public SimPanel(boolean debug) {
		setBackground(new Color(255, 255, 255));
        setLayout(new GridLayout(0, 3, 0, 0));
        
        simPayloadStatus =  new ArrayList<JTextField>(3);
        
        simPayloadStatus.add(new JTextField("Payload 1:"));
        simPayloadStatus.get(0).setFont(new Font("Tahoma", Font.BOLD, 14));
        simPayloadStatus.get(0).setEditable(false);
        simPayloadStatus.get(0).setColumns(10);
        add(simPayloadStatus.get(0));
        
        simPayloadStatus.add(new JTextField("Payload 2:"));
        simPayloadStatus.get(1).setEditable(false);
        simPayloadStatus.get(1).setFont(new Font("Tahoma", Font.BOLD, 14));
        simPayloadStatus.get(1).setColumns(10);
        add(simPayloadStatus.get(1));

        simPayloadStatus.add(new JTextField("Payload 3:"));
        simPayloadStatus.get(2).setEditable(false);
        simPayloadStatus.get(2).setFont(new Font("Tahoma", Font.BOLD, 14));
        simPayloadStatus.get(2).setColumns(10);
        add(simPayloadStatus.get(2));

        JLabel label = new JLabel("");
        add(label);
        
        JLabel label_1 = new JLabel("");
        add(label_1);

        JLabel label_2 = new JLabel("");
        add(label_2);
        JLabel label_4 = new JLabel("");
        add(label_4);
                
        comboBox = new JComboBox();
        add(comboBox);
        comboBox.setFont(new Font("Tahoma", Font.BOLD, 16));
        comboBox.setModel( new DefaultComboBoxModel<Object>(new String[] { "Option 1", "Option 2", "Option 3", "Option 4", "Option 5","Option 6"}));
        add(comboBox);

        JLabel label_5 = new JLabel("");
        add(label_5);

        JLabel label_6 = new JLabel("");
        add(label_6);

        JLabel label_7 = new JLabel("");
        add(label_7);
        
        JLabel label_8 = new JLabel("");
        add(label_8);
        
        JLabel label_9 = new JLabel("");
        add(label_9);
        
        if(debug){
	        textField = new JTextField();
	        textField.setEnabled(false);
	        textField.setEditable(false);
	        add(textField);
	        textField.setColumns(10);
        }else{
        	JLabel label_10 = new JLabel("");
            add(label_10);
        }
        
        JLabel label_11 = new JLabel("");
        add(label_11);
        
        JLabel label_12 = new JLabel("");
        add(label_12);

        btnSend = new JButton("Send Command");
        btnSend.setFont(new Font("Tahoma", Font.BOLD, 16));
        btnSend.setBackground(Status.skyblue);
        add(btnSend);
        
        JLabel label_13 = new JLabel("");
        add(label_13);
        
        JLabel label_14 = new JLabel("");
        add(label_14);
        
        btnAbort = new JButton("Abort");
        btnAbort.setFont(new Font("Tahoma", Font.BOLD, 16));
        btnAbort.setBackground(Status.lightYellow);
        add(btnAbort);
        
        JLabel label_15 = new JLabel("");
        add(label_15);
	}
	
    //Checks and returns the selected JRadioButton
    public int checkButtons(){
    	return comboBox.getSelectedIndex() + 1;
        /*if(functionBtn.get(0).isSelected()) return 1;
        if(functionBtn.get(1).isSelected()) return 2;
        if(functionBtn.get(2).isSelected()) return 3;
        if(functionBtn.get(3).isSelected()) return 4;
        if(functionBtn.get(4).isSelected()) return 5;
        if(functionBtn.get(5).isSelected()) return 6;
        */
        //return 0;	
    }
    

}
