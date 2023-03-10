/*
 * Name: Connor Cerisano
 * Date: 2019/06/10
 * Purpose: JPanel Graphical Interface ("Pizza" Clicker Game)
 */
package pizzaclickergame;

import java.awt.BorderLayout;
import javax.swing.*;
import java.util.TimerTask;

public class mainScreen extends javax.swing.JPanel {

    JFrame newFrame = new JFrame(); //Create a JFrame to handle our game's GUI
    java.util.Timer t = new java.util.Timer(); //Timer; used for auto-upgrades and text colors
    PizzaClickerGame sliceSystem = new PizzaClickerGame(); //Handles all upgrade-related tasks

    public mainScreen() {
        initComponents(); //Do not remove!

        //JFRAME Properties
        newFrame.getContentPane().add(this, BorderLayout.CENTER);
        newFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        newFrame.pack();
        newFrame.setVisible(true);
        newFrame.setTitle("Pizza Clicker");

        //Initiate our slice count
        sliceSystem.displaySliceCount(sliceValue);

        //Import and set images
        ImageIcon pizzaIcon = new ImageIcon("pizzaIcon.png");
        pizzaButton.setText(""); //Clear text used for the "design" tab
        pizzaButton.setIcon(pizzaIcon);

        ImageIcon gameIcon = new ImageIcon("gameIcon.png");
        gameIconLabel.setText(""); //Clear text only used for the "design" tab
        gameIconLabel.setIcon(gameIcon);

        //SLICE TIMER; Increase the slice count so much depending on each upgrade's power.
        t.schedule(new TimerTask() {
            @Override
            public void run() {
                sliceSystem.updateSliceCount(); //Update the slice count
                sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count after changing the value
            }
        }, 1000, 1000); //Execute code in run() every second.

        //"FAST" TIMER; Mainly used for upgrade availability, but also used to refresh our slices made per second.
        t.schedule(new TimerTask() {
            @Override
            public void run() {
                //Update the text color of each upgrade. This method also checks for upgrade availability.
                sliceSystem.updateTextColors(clickPowerUpgrade, 0);
                sliceSystem.updateTextColors(ovenUpgrade, 1);
                sliceSystem.updateTextColors(bakeryUpgrade, 2);
                sliceSystem.updateTextColors(employeeUpgrade, 3);
                sliceSystem.updateTextColors(truckUpgrade, 4);
                sliceSystem.updateTextColors(conglomerateUpgrade, 5);
                sliceSystem.updateTextColors(empireUpgrade, 6);
                sliceSystem.updateTextColors(worldUpgrade, 7);

                //Refresh slice count per second
                sliceSystem.displaySlicesPerSecond(spsLabel);
            }
        }, 50, 50); //Execute code in run() at a fast rate.

    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        pizzaButton = new javax.swing.JButton();
        sliceValue = new javax.swing.JLabel();
        clickPowerUpgrade = new javax.swing.JButton();
        ovenUpgrade = new javax.swing.JButton();
        gameIconLabel = new javax.swing.JLabel();
        spsLabel = new javax.swing.JLabel();
        bakeryUpgrade = new javax.swing.JButton();
        employeeUpgrade = new javax.swing.JButton();
        truckUpgrade = new javax.swing.JButton();
        conglomerateUpgrade = new javax.swing.JButton();
        empireUpgrade = new javax.swing.JButton();
        worldUpgrade = new javax.swing.JButton();

        setMaximumSize(new java.awt.Dimension(923, 399));
        setMinimumSize(new java.awt.Dimension(922, 398));

        pizzaButton.setText("pizzaButton");
        pizzaButton.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        pizzaButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                pizzaButtonActionPerformed(evt);
            }
        });

        sliceValue.setFont(new java.awt.Font("Times New Roman", 1, 24)); // NOI18N
        sliceValue.setText("sliceValue");
        sliceValue.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);

        clickPowerUpgrade.setText("UPGRADE: Click Power (Cost: 10 slices) || Click power: +0 per click");
        clickPowerUpgrade.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                clickPowerUpgradeActionPerformed(evt);
            }
        });

        ovenUpgrade.setText("UPGRADE: Oven (Cost: 20 slices) || You currently have no ovens.");
        ovenUpgrade.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ovenUpgradeActionPerformed(evt);
            }
        });

        gameIconLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        gameIconLabel.setText("gameIcon");
        gameIconLabel.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);

        spsLabel.setText("Slices Per Second: 0");
        spsLabel.setVerticalAlignment(javax.swing.SwingConstants.TOP);

        bakeryUpgrade.setText("UPGRADE: Bakery (Cost: 100 slices) || You currently have no bakeries.");
        bakeryUpgrade.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bakeryUpgradeActionPerformed(evt);
            }
        });

        employeeUpgrade.setText("UPGRADE: Employee (Cost: 5000 slices) || You currently have no employees.");
        employeeUpgrade.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                employeeUpgradeActionPerformed(evt);
            }
        });

        truckUpgrade.setText("UPGRADE: Pizza Truck (Cost: 10000 slices) || You currently have no trucks.");
        truckUpgrade.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                truckUpgradeActionPerformed(evt);
            }
        });

        conglomerateUpgrade.setText("UPGRADE: Conglomerate (Cost: 100000 slices) || You currently have no conglomerates.");
        conglomerateUpgrade.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                conglomerateUpgradeActionPerformed(evt);
            }
        });

        empireUpgrade.setText("UPGRADE: Empire (Cost: 500000 slices) || You currently have no empires.");
        empireUpgrade.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                empireUpgradeActionPerformed(evt);
            }
        });

        worldUpgrade.setText("UPGRADE: Pizza World (Cost: 50000000 slices) || You currently have no pizza worlds.");
        worldUpgrade.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                worldUpgradeActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(gameIconLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 128, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(sliceValue, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(spsLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(pizzaButton, javax.swing.GroupLayout.PREFERRED_SIZE, 216, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(ovenUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, 1304, Short.MAX_VALUE)
                            .addComponent(bakeryUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(clickPowerUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(employeeUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(truckUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, 706, Short.MAX_VALUE)
                            .addComponent(empireUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(conglomerateUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(worldUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(gameIconLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 170, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(sliceValue, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(spsLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(pizzaButton, javax.swing.GroupLayout.PREFERRED_SIZE, 215, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(clickPowerUpgrade, javax.swing.GroupLayout.PREFERRED_SIZE, 46, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(ovenUpgrade, javax.swing.GroupLayout.PREFERRED_SIZE, 46, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(bakeryUpgrade, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(employeeUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(conglomerateUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, 44, Short.MAX_VALUE)
                    .addComponent(truckUpgrade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(empireUpgrade, javax.swing.GroupLayout.PREFERRED_SIZE, 46, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(worldUpgrade, javax.swing.GroupLayout.PREFERRED_SIZE, 46, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(19, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    //--------------------------------BUTTON METHODS--------------------------------
    private void pizzaButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_pizzaButtonActionPerformed
        sliceSystem.pizzaClick(); //Add slices based on click and the clicking power upgrade
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_pizzaButtonActionPerformed

    private void clickPowerUpgradeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_clickPowerUpgradeActionPerformed
        sliceSystem.upgradeClickPower(clickPowerUpgrade); //Buy upgrade; calculate new upgrade cost and update button text.
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_clickPowerUpgradeActionPerformed

    private void ovenUpgradeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ovenUpgradeActionPerformed
        sliceSystem.upgradeOven(ovenUpgrade); //Buy upgrade; calculate new upgrade cost and update button text.
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_ovenUpgradeActionPerformed

    private void employeeUpgradeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_employeeUpgradeActionPerformed
        sliceSystem.upgradeEmployee(employeeUpgrade); //Buy upgrade; calculate new upgrade cost and update button text.
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_employeeUpgradeActionPerformed

    private void empireUpgradeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_empireUpgradeActionPerformed
        sliceSystem.upgradeEmpire(empireUpgrade); //Buy upgrade; calculate new upgrade cost and update button text.
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_empireUpgradeActionPerformed

    private void bakeryUpgradeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bakeryUpgradeActionPerformed
        sliceSystem.upgradeBakery(bakeryUpgrade); //Buy upgrade; calculate new upgrade cost and update button text.
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_bakeryUpgradeActionPerformed

    private void truckUpgradeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_truckUpgradeActionPerformed
        sliceSystem.upgradeTruck(truckUpgrade); //Buy upgrade; calculate new upgrade cost and update button text.
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_truckUpgradeActionPerformed

    private void conglomerateUpgradeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_conglomerateUpgradeActionPerformed
        sliceSystem.upgradeConglomerate(conglomerateUpgrade); //Buy upgrade; calculate new upgrade cost and update button text.
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_conglomerateUpgradeActionPerformed

    private void worldUpgradeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_worldUpgradeActionPerformed
        sliceSystem.upgradeWorld(worldUpgrade); //Buy upgrade; calculate new upgrade cost and update button text.
        sliceSystem.displaySliceCount(sliceValue); //Refresh our slice count
    }//GEN-LAST:event_worldUpgradeActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton bakeryUpgrade;
    private javax.swing.JButton clickPowerUpgrade;
    private javax.swing.JButton conglomerateUpgrade;
    private javax.swing.JButton empireUpgrade;
    private javax.swing.JButton employeeUpgrade;
    private javax.swing.JLabel gameIconLabel;
    private javax.swing.JButton ovenUpgrade;
    private javax.swing.JButton pizzaButton;
    private javax.swing.JLabel sliceValue;
    private javax.swing.JLabel spsLabel;
    private javax.swing.JButton truckUpgrade;
    private javax.swing.JButton worldUpgrade;
    // End of variables declaration//GEN-END:variables
}
