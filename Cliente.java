import java.io.*;
import java.net.*;

public class Cliente {
    public static void main(String[] args) throws IOException {
        
        if (args.length != 2) {
            System.err.println(
                "Uso desde consola: java Cliente_de_Eco <nombre de host (computadora)> <numero puerto>");
            System.exit(1);
        }

        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);

        try (
            Socket echoSocket = new Socket(hostName, portNumber);
            PrintWriter out = new PrintWriter(echoSocket.getOutputStream(), true);
            
            BufferedReader in = new BufferedReader(new InputStreamReader(echoSocket.getInputStream()));
            BufferedReader stdIn = new BufferedReader( new InputStreamReader(System.in))
        ) {
            String inputLine;
            out.println("15\0");
            /*try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }*/
            out.println("Hola servidor.\0");
            //while ((inputLine = in.readLine()) != null) {
                inputLine = in.readLine();
                System.out.println("Cantidad de caracteres del mensaje del servidor: " + inputLine);
            //}
            //while ((inputLine = in.readLine()) != null) {
                inputLine = in.readLine();
                System.out.println("Mensaje del servidor: " + inputLine);
            //}
           
        } catch (UnknownHostException e) {
            System.err.println("No conozco al host " + hostName);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("no se pudo obtener E/S para la conexion " +
                hostName);
            System.exit(1);
        } 
    }
}
