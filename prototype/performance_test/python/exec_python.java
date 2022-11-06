import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Field;






class exec_python {
    public static void main(String[] args) {
        try {
            Runtime rt = Runtime.getRuntime();
            String cmd = "ls -l";
            Process pr = rt.exec(cmd);
            System.out.println(pr.getClass().getName());

            long pid = -1;
            
            // Phương pháp truy cập private field trong java sử dụng reflection
            if (pr.getClass().getName().equals("java.lang.UNIXProcess")) {
                Field f = pr.getClass().getDeclaredField("pid");
                f.setAccessible(true);
                pid = f.getLong(pr);
                f.setAccessible(false);
            }

            System.out.println(pid);
                

            // Code to get the result from runtime process
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(pr.getInputStream()));

            BufferedReader stdError = new BufferedReader(new InputStreamReader(pr.getErrorStream()));

            // Read the output from the command
            System.out.println("Here is the standard output of the command:\n");
            String s = null;
            while ((s = stdInput.readLine()) != null) {
                System.out.println(s);
            }

            // Read any errors from the attempted command
            System.out.println("Here is the standard error of the command (if any):\n");
            while ((s = stdError.readLine()) != null) {
                System.out.println(s);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}