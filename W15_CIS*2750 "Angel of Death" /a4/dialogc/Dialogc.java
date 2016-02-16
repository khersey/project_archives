package dialogc;

import javax.swing.*;

public class Dialogc {
    public static void main(String args[]) {

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                Gui myGui = new Gui();
                myGui.setVisible(true);
            }
        });

    }
}
