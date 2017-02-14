package view;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.border.LineBorder;

public class SimPanel extends JPanel {
	
	public ArrayList<JTextField> simPayloadStatus;
    public ArrayList<JRadioButton> functionBtn;
    public ButtonGroup simBtnGroup = new ButtonGroup();
    public JButton btnSend;
	/**
	 * Create the panel.
	 */
	public SimPanel() {
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

        functionBtn = new ArrayList<JRadioButton>(); 
    
        for(int i = 0; i < 6; i++){
        	functionBtn.add(new JRadioButton("Simultaneous Function " + (i + 1)));
            simBtnGroup.add(functionBtn.get(i));
            functionBtn.get(i).setBorderPainted(true);
            functionBtn.get(i).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
            functionBtn.get(i).setFont(new Font("Tahoma", Font.BOLD, 14));
            add(functionBtn.get(i));
            functionBtn.get(i).addActionListener(new ActionListener() {
            	public void actionPerformed(ActionEvent arg0) {
            		updateSelection();
            	}
            });
        }

        JLabel label_3 = new JLabel("");
        add(label_3);

        JLabel label_4 = new JLabel("");
        add(label_4);

        JLabel label_5 = new JLabel("");
        add(label_5);

        JLabel label_6 = new JLabel("");
        add(label_6);

        btnSend = new JButton("Send Command");

        btnSend.setFont(new Font("Tahoma", Font.BOLD, 16));
        add(btnSend);

        JLabel label_7 = new JLabel("");
        add(label_7);
        
        updateSelection();
	}
	
    //Checks and returns the selected JRadioButton
    public int checkButtons(){
        if(functionBtn.get(0).isSelected()) return 1;
        if(functionBtn.get(1).isSelected()) return 2;
        if(functionBtn.get(2).isSelected()) return 3;
        if(functionBtn.get(3).isSelected()) return 4;
        if(functionBtn.get(4).isSelected()) return 5;
        if(functionBtn.get(5).isSelected()) return 6;
        return 0;	
    }
    
    public void updateSelection(){
    	for(int i = 0; i < 6; i++){
    		if((i + 1) == checkButtons()){
    			functionBtn.get(i).setBackground(Color.LIGHT_GRAY);
    			functionBtn.get(i).setForeground(Color.blue);
    			
    		}else{
    			functionBtn.get(i).setBackground(Color.GRAY);
    			functionBtn.get(i).setForeground(Color.LIGHT_GRAY);
    		}
    	}
    }
    

}
