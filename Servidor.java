

import java.net.*; // paquete que contienen clases de red , todo lo necesario para comunicarme en red

import java.io.*; // paquete que contienen clases para E/S teclado y monitor

public class Servidor {
    
    public static void main(String[] args) throws IOException {
        
        if (args.length != 1) {
            System.err.println("Uso desde consola:  <numero puerto>");

            System.exit(1);
        }
        
        int portNumber = Integer.parseInt(args[0]);
        
        try (
            ServerSocket serverSocket =
                new ServerSocket(Integer.parseInt(args[0]));
            Socket clientSocket = serverSocket.accept();     
            PrintWriter out =
                new PrintWriter(clientSocket.getOutputStream(), true);                   
            BufferedReader in = new BufferedReader(
                new InputStreamReader(clientSocket.getInputStream()));
        ) {
            String inputLine;
            //while ((inputLine = in.readLine()) != null) {
                inputLine = in.readLine();
                System.out.println("Cantidad de caracteres, especificados por el cliente conectado: " + inputLine);
            //}
            //while ((inputLine = in.readLine()) != null) {
                inputLine = in.readLine();
                System.out.println("Mensaje recibido, enviado por el cliente conectado: " + inputLine);
            //}
            out.println("14\0");
            /*try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }*/
            out.println("Hola cliente.\0");
        } catch (IOException e) {
            System.out.println(" ocurrio una excepcion cuando intentamos escuchar "
                + portNumber + " o esperando por una conexicon");
            System.out.println(e.getMessage());
        }
    }
}
