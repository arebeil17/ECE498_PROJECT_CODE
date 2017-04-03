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
import javax.swing.JComboBox;

public class SimPanel extends JPanel {
	
	public ArrayList<JTextField> simPayloadStatus;
    //public ArrayList<JRadioButton> functionBtn;
    public ButtonGroup simBtnGroup = new ButtonGroup();
    public JComboBox comboBox;
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
        /*
        functionBtn = new ArrayList<JRadioButton>(); 

        functionBtn.add(new JRadioButton("Simultaneous Function 1"));
        simBtnGroup.add(functionBtn.get(0));
        functionBtn.get(0).setBorderPainted(true);
        functionBtn.get(0).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        functionBtn.get(0).setFont(new Font("Tahoma", Font.BOLD, 12));
        add(functionBtn.get(0));

        functionBtn.add(new JRadioButton("Simultaneous Function 2"));
        simBtnGroup.add(functionBtn.get(1));
        functionBtn.get(1).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(1).setBorderPainted(true);
        functionBtn.get(1).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        add(functionBtn.get(1));

        functionBtn.add(new JRadioButton("Simultaneous Function 3"));
        simBtnGroup.add(functionBtn.get(2));
        functionBtn.get(2).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(2).setBorderPainted(true);
        functionBtn.get(2).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        add(functionBtn.get(2));

        functionBtn.add(new JRadioButton("Simultaneous Function 4"));
        simBtnGroup.add(functionBtn.get(3));
        functionBtn.get(3).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(3).setBorderPainted(true);
        functionBtn.get(3).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        add(functionBtn.get(3));

        functionBtn.add(new JRadioButton("Simultaneous Function 5"));
        simBtnGroup.add(functionBtn.get(4));
        functionBtn.get(4).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(4).setBorderPainted(true);
        functionBtn.get(4).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        add(functionBtn.get(4));

        functionBtn.add(new JRadioButton("Simultaneous Function 6"));
        simBtnGroup.add(functionBtn.get(5));
        functionBtn.get(5).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(5).setBorderPainted(true);
        functionBtn.get(5).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        add(functionBtn.get(5));
         */
        
        JLabel label_8 = new JLabel("");
        add(label_8);
        
        JLabel label_9 = new JLabel("");
        add(label_9);

        btnSend = new JButton("Send Command");

        btnSend.setFont(new Font("Tahoma", Font.BOLD, 16));
        add(btnSend);
        
        JLabel label_10 = new JLabel("");
        add(label_10);
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
