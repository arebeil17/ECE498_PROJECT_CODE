/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.FlowLayout;
import javax.swing.JTabbedPane;
import java.awt.Font;
import java.awt.SystemColor;
import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.BoxLayout;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.JTextField;
import javax.swing.SpringLayout;
import javax.swing.JRadioButton;
import javax.swing.border.LineBorder;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.LayoutStyle.ComponentPlacement;
import java.awt.GridLayout;
import javax.swing.ButtonGroup;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

public class MPB_GUI extends JFrame{
    
    private JPanel contentPane;
    private JTextField txtPayload2;
    private JTextField txtPayload3;
    private JTextField txtPayload1;
    public ButtonGroup simBtnGroup = new ButtonGroup();
    public JButton btnConfirm;
    public ArrayList<JRadioButton> functionBtn;

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
            EventQueue.invokeLater(new Runnable() {
                    public void run() {
                            try {
                                    MPB_GUI frame = new MPB_GUI();
                                    frame.setVisible(true);
                            } catch (Exception e) {
                                    e.printStackTrace();
                            }
                    }
            });
    }

    /**
     * Create the frame.
     */
    public MPB_GUI() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 800, 480);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(new BorderLayout(0, 0));

        JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
        tabbedPane.setBackground(SystemColor.inactiveCaption);
        tabbedPane.setFont(new Font("Tahoma", Font.BOLD, 18));
        contentPane.add(tabbedPane);

        JPanel SimPanel = new JPanel();
        SimPanel.setBackground(new Color(255, 255, 255));
        tabbedPane.addTab("Simultaneous", null, SimPanel, null);
        SimPanel.setLayout(new GridLayout(0, 3, 0, 0));

        txtPayload1 = new JTextField();
        txtPayload1.setText("Payload 1:");
        txtPayload1.setFont(new Font("Tahoma", Font.BOLD, 14));
        txtPayload1.setEditable(false);
        txtPayload1.setColumns(10);
        SimPanel.add(txtPayload1);

        txtPayload2 = new JTextField();
        txtPayload2.setEditable(false);
        txtPayload2.setText("Payload 2:");
        txtPayload2.setFont(new Font("Tahoma", Font.BOLD, 14));
        txtPayload2.setColumns(10);
        SimPanel.add(txtPayload2);

        txtPayload3 = new JTextField();
        txtPayload3.setEditable(false);
        txtPayload3.setText("Payload 3:");
        txtPayload3.setFont(new Font("Tahoma", Font.BOLD, 14));
        txtPayload3.setColumns(10);
        SimPanel.add(txtPayload3);

        JLabel label = new JLabel("");
        SimPanel.add(label);

        JLabel label_1 = new JLabel("");
        SimPanel.add(label_1);

        JLabel label_2 = new JLabel("");
        SimPanel.add(label_2);

        functionBtn = new ArrayList<JRadioButton>(); 

        functionBtn.add(new JRadioButton("Simultaneous Function 1"));
        simBtnGroup.add(functionBtn.get(0));
        functionBtn.get(0).setBorderPainted(true);
        functionBtn.get(0).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        functionBtn.get(0).setFont(new Font("Tahoma", Font.BOLD, 12));
        SimPanel.add(functionBtn.get(0));

        functionBtn.add(new JRadioButton("Simultaneous Function 2"));
        simBtnGroup.add(functionBtn.get(1));
        functionBtn.get(1).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(1).setBorderPainted(true);
        functionBtn.get(1).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        SimPanel.add(functionBtn.get(1));

        functionBtn.add(new JRadioButton("Simultaneous Function 3"));
        simBtnGroup.add(functionBtn.get(2));
        functionBtn.get(2).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(2).setBorderPainted(true);
        functionBtn.get(2).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        SimPanel.add(functionBtn.get(2));

        functionBtn.add(new JRadioButton("Simultaneous Function 4"));
        simBtnGroup.add(functionBtn.get(3));
        functionBtn.get(3).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(3).setBorderPainted(true);
        functionBtn.get(3).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        SimPanel.add(functionBtn.get(3));

        functionBtn.add(new JRadioButton("Simultaneous Function 5"));
        simBtnGroup.add(functionBtn.get(4));
        functionBtn.get(4).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(4).setBorderPainted(true);
        functionBtn.get(4).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        SimPanel.add(functionBtn.get(4));

        functionBtn.add(new JRadioButton("Simultaneous Function 6"));
        simBtnGroup.add(functionBtn.get(5));
        functionBtn.get(5).setFont(new Font("Tahoma", Font.BOLD, 12));
        functionBtn.get(5).setBorderPainted(true);
        functionBtn.get(5).setBorder(new LineBorder(new Color(0, 0, 0), 1, true));
        SimPanel.add(functionBtn.get(5));

        JLabel label_3 = new JLabel("");
        SimPanel.add(label_3);

        JLabel label_4 = new JLabel("");
        SimPanel.add(label_4);

        JLabel label_5 = new JLabel("");
        SimPanel.add(label_5);

        JLabel label_6 = new JLabel("");
        SimPanel.add(label_6);

        btnConfirm = new JButton("Send Command");

        btnConfirm.setFont(new Font("Tahoma", Font.BOLD, 16));
        SimPanel.add(btnConfirm);

        JLabel label_7 = new JLabel("");
        SimPanel.add(label_7);

        JPanel IndependentPanel = new JPanel();
        IndependentPanel.setBackground(SystemColor.control);
        tabbedPane.addTab("Independent", null, IndependentPanel, null);
        IndependentPanel.setLayout(new BorderLayout(0, 0));
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
}
