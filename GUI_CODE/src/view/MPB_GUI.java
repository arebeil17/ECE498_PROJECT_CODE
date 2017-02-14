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
import javax.swing.JTabbedPane;
import java.awt.Font;
import java.awt.SystemColor;
import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JRadioButton;
import javax.swing.border.LineBorder;
import java.awt.GridLayout;
import javax.swing.ButtonGroup;
import javax.swing.DefaultComboBoxModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import model.Status;
import java.util.ArrayList;
import java.awt.FlowLayout;
import javax.swing.JComboBox;
import javax.swing.JToggleButton;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.UIManager;
import javax.swing.UIManager.*;

public class MPB_GUI extends JFrame{
    
    private JPanel contentPane;
    private JTabbedPane tabbedPane;
    private int tabSelected = 0;
    
    public SimPanel simPanel; 
    public IndependentPanel independentPanel;
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

        tabbedPane = new JTabbedPane(JTabbedPane.TOP);
        tabbedPane.setBackground(SystemColor.inactiveCaption);
        tabbedPane.setFont(new Font("Tahoma", Font.BOLD, 20));
        contentPane.add(tabbedPane);

        initSimPanel();
        
        initIndependentPanel();
        
        //Add listener to track change of current tab
        tabbedPane.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if (e.getSource() instanceof JTabbedPane) {
                    JTabbedPane pane = (JTabbedPane) e.getSource();
                    System.out.println("Selected tab #: " + pane.getSelectedIndex());
                    tabSelected = pane.getSelectedIndex();
                    Status.mode = tabSelected;
                }
            }
        });
        
    }
    
    private void initSimPanel(){
    	simPanel = new SimPanel();
    	simPanel.setBackground(SystemColor.control);
    	tabbedPane.addTab("Simultaneous", null, simPanel, null);
    }
    
    private void initIndependentPanel(){
    	independentPanel = new IndependentPanel();
        independentPanel.setBackground(SystemColor.control);
        tabbedPane.addTab("Independent", null, independentPanel, null);
    }
    
	public int getTabSelected() {
		return tabSelected;
	}

	public void setTabSelected(int tabSelected) {
		this.tabSelected = tabSelected;
	}
}
