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
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import model.DataBuffer;
import model.Status;
import javax.swing.UIManager;
import javax.swing.UIManager.*;
import javax.swing.ImageIcon;
import java.awt.GridLayout;

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
    	Status.initialize();
        DataBuffer.initialize(64);
        try {
            for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (Exception e) {
            // If Nimbus is not available, you can set the GUI to another look and feel.
        }
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
        tabbedPane.setBackground(SystemColor.activeCaption);
        tabbedPane.setFont(new Font("Tahoma", Font.BOLD, 18));
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
                    simPanel.simPayloadStatus.get(0).setText("Payload 1:  "+ Status.module.get(0).idString());
                    simPanel.simPayloadStatus.get(1).setText("Payload 2:  "+ Status.module.get(1).idString());
                    simPanel.simPayloadStatus.get(2).setText("Payload 3:  "+ Status.module.get(2).idString());
                    independentPanel.indePayloadStatus.get(0).setText("Payload 1:  "+ Status.module.get(0).idString());
                    independentPanel.indePayloadStatus.get(1).setText("Payload 2:  "+ Status.module.get(1).idString());
                    independentPanel.indePayloadStatus.get(2).setText("Payload 3:  "+ Status.module.get(2).idString());
                }
            }
        });
        
      //Add listener to track change of current tab
        simPanel.comboBox.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent arg0) {
            	System.out.println("Option Selected: " + simPanel.checkButtons());
            }	
        });
        
    }
    
    private void initSimPanel(){
    	simPanel = new SimPanel(false);
    	simPanel.setBackground(SystemColor.controlShadow);
    	tabbedPane.addTab("Simultaneous", null, simPanel, null);
    }
    
    private void initIndependentPanel(){
    	independentPanel = new IndependentPanel(false);
    	GridLayout gridLayout = (GridLayout) independentPanel.getLayout();
    	independentPanel.setOpaque(true);
        independentPanel.setBackground(SystemColor.controlShadow);
        tabbedPane.addTab("Independent", null, independentPanel, null);
    }
    
	public int getTabSelected() {
		return tabSelected;
	}

	public void setTabSelected(int tabSelected) {
		this.tabSelected = tabSelected;
	}
}
