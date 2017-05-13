import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Form used to order a custom computer.
 *
 * <p>Homework 11 -- GUIs</p>
 */
public class ComputerOrderForm{
    /**
     * Text fields used for input.
     */
    private JTextField brandJTextField;
    private JTextField cpuCoresJTextField;
    private JTextField gpuCoresJTextField;
    private JTextField ramAmountJTextField;
    private JTextField powerSupplyJTextField;
    private JTextField hdCapacityJTextField;

    /**
     * Buttons used to handle user interaction.
     */
    private JButton calcPriceJButton;
    private JButton clearJButton;
    static JFrame mainJFrame;

    /**
     * Starting prices for each computer brand
     */
    private static final double APPLE_PRICE = 999.0;
    private static final double DELL_PRICE = 899.0;
    private static final double MICROSOFT_PRICE = 849.0;
    private static final double ASUS_PRICE = 799.0;
    private static final double HP_PRICE = 749.0;

    /**
     * Price multipliers for each component.
     */
    private static final double PER_CPU_CORE_PRICE = 100.0;
    private static final double PER_GPU_CORE_PRICE = 150.0;
    private static final double PER_RAM_GB_PRICE = 25.0;
    private static final double PER_HD_GB_PRICE = 1.0;
    private static final double PER_SUPPLY_WATT_PRICE = 0.25;

    /**
     * Constructs a newly allocated {@code ComputerOrderForm} object.
     */

    public ComputerOrderForm(){
        this.setUpGUI();
        this.calcPriceJButton.addActionListener(new ActionListener(){
          public void actionPerformed(ActionEvent e){
            String brandText = brandJTextField.getText();
            String numC = cpuCoresJTextField.getText();
            String numG = gpuCoresJTextField.getText();
            String ramAmt = ramAmountJTextField.getText();
            String powerAmt = powerSupplyJTextField.getText();
            String hdAmt = hdCapacityJTextField.getText();

            double brandPrice = 0;
            double corePrice = 0;
            double gcorePrice = 0;
            double ramPrice = 0;
            double powerPrice = 0;
            double hdPrice = 0;

            if(brandText.equals("Apple")){
              brandPrice = 999.0;
            }else if(brandText.equals("Dell")){
              brandPrice = 899.0;
            }else if(brandText.equals("Microsoft")){
              brandPrice = 849.0;
            }else if(brandText.equals("Asus")){
              brandPrice = 799.0;
            }else if(brandText.equals("HP")){
              brandPrice = 749.0;
            }else{
              JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid brand! Please enter another!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
            }

            if(numC.length() > 0){
                int numCores = Integer.parseInt(numC);
                if(numCores < 0){
                  JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid amount of CPU cores! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
                }else{
                  corePrice = 100.0 * numCores;
                }
            }else{
              JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid amount of CPU cores! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
            }

            if(numG.length() > 0){
              int numGcores = Integer.parseInt(numG);
              if(numGcores < 0){
                JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid amount of GPU cores! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
              }else{
                gcorePrice = 150.0 * numGcores;
              }
            }else{
              JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid amount of GPU cores! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
            }

            if(ramAmt.length() > 0){
              int ramAmnt = Integer.parseInt(ramAmt);
              if(ramAmnt < 0){
                JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid amount of RAM! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
              }else{
                ramPrice = 25.0 * ramAmnt;
              }
            }else{
              JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid amount of RAM! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
            }

            if(powerAmt.length() > 0){
              int powerAmnt = Integer.parseInt(powerAmt);
              if(powerAmnt < 0){
                JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid power supply wattage! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
              }else{
                powerPrice = 0.25 * powerAmnt;
              }
            }else{
              JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid power supply wattage! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
            }

            if(hdAmt.length() > 0){
              int hdAmnt = Integer.parseInt(hdAmt);
              if(hdAmnt < 0){
                JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid HD capacity! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
              }else{
                hdPrice = 1.0 * hdAmnt;
                Double totalCost = new Double(brandPrice + corePrice + gcorePrice + ramPrice + powerPrice + hdPrice);
                totalCost = Math.round(totalCost*100.0)/100.0;
                String outputString = "Price: $" + totalCost;
                JOptionPane.showMessageDialog(mainJFrame, outputString,"Computer Order Form",JOptionPane.INFORMATION_MESSAGE);
              }
            }else{
              JOptionPane.showMessageDialog(mainJFrame, "Error: Invalid HD capacity! Please enter a positive number!","Computer Order Form",JOptionPane.ERROR_MESSAGE);
            }
          }
        });

        this.clearJButton.addActionListener(new ActionListener(){
          public void actionPerformed(ActionEvent e){
            brandJTextField.setText("");
            cpuCoresJTextField.setText("");
            gpuCoresJTextField.setText("");
            ramAmountJTextField.setText("");
            powerSupplyJTextField.setText("");
            hdCapacityJTextField.setText("");
            brandJTextField.requestFocus();
          }
        });
    } //ComputerOrderForm

    /**
     * Sets up the GUI for the user.
     */
    private void setUpGUI() {
        //initialize the components
        this.brandJTextField = new JTextField();
        this.cpuCoresJTextField = new JTextField();
        this.gpuCoresJTextField = new JTextField();
        this.ramAmountJTextField = new JTextField();
        this.powerSupplyJTextField = new JTextField();
        this.hdCapacityJTextField = new JTextField();
        this.calcPriceJButton = new JButton("Calculate Price");
        this.clearJButton = new JButton("Clear Form");

        mainJFrame = new JFrame("Computer Order Form");
        JPanel mainJPanel = new JPanel();

        //format mainJPanel
        mainJPanel.setLayout(new GridLayout(14, 1));
        mainJPanel.setBorder(new EmptyBorder(5, 5, 5, 5));

        //add the components to mainJPanel
        mainJPanel.add(new JLabel("Brand:"));
        mainJPanel.add(this.brandJTextField);
        mainJPanel.add(new JLabel("CPU cores:"));
        mainJPanel.add(this.cpuCoresJTextField);
        mainJPanel.add(new JLabel("GPU cores:"));
        mainJPanel.add(this.gpuCoresJTextField);
        mainJPanel.add(new JLabel("RAM amount:"));
        mainJPanel.add(this.ramAmountJTextField);
        mainJPanel.add(new JLabel("Power supply wattage:"));
        mainJPanel.add(this.powerSupplyJTextField);
        mainJPanel.add(new JLabel("HD capacity:"));
        mainJPanel.add(this.hdCapacityJTextField);
        mainJPanel.add(this.calcPriceJButton);
        mainJPanel.add(this.clearJButton);

        //format mainJFrame
        mainJFrame.setMinimumSize(new Dimension(500, 450));
        mainJFrame.setContentPane(mainJPanel);
        mainJFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        mainJFrame.setLocationRelativeTo(null);
        mainJFrame.pack();

        //make mainJFrame visible
        mainJFrame.setVisible(true);
    } //setUpGUI

    public static void main(String[] args) {
        new ComputerOrderForm();
    } //main
}
