/*
 * ClientRMI
 */

 class ClientRMI {
    public static void main (String[] args) {
        int REGISTRYPORT = 1099;
        int temp;
        String registryHost = null;
        String serviceName = "ServerRMI";
        
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in))
        try{
            if(args.length != 1 &&  args.length != 2) {
                System.out.println("Sintassi: ... NomeHost [registryport]");
                System.exit(1);
            }

            registryHost = args[0];

            if(args.length == 2) {
                try{
                    temp = Integer.parseInt(args[1]);

                    // check di validità della porta messa
                    if(temp < 1024 || temp > 65536) {
                    System.out.println("Il valore della porta deve essere un intero valido,
                        compreso tra 1024 e 65536")
                    }
                }catch(Exception e) {
                    System.out.println("Errore: necessità di un intero in input");
                }

                
            }

            // Connessione al servizio RMI remoto
            String completeName = "//" + registryHost + ":" +
            REGISTRYPORT + "/" + serviceName;
            ServerRMI serverRMI =
            (ServerRMI) Naming.lookup (completeName);

            System.out.println("\nRichieste a EOF");
            System.out.print("Servizio(C = conta righe, E = elimina righe): ");

            String service;
            while((service = stdIn.readLine())!=null) {

                if(service.equals("C")) {

                    System.out.println("Inserire nome del file su cui si vuole operare e intero con seguente sintassi: FileName Num")

                    String[] split = stdIn.readLIne().split(" ");
                    String file = split[0];
                    int num = Integer.parseInt(split[1]);

                    try{
                        int result = serverRMI.conta_righe(file, num);
                        System.out.println("Conta righe effettuata sul file " + file + ": righe con più di " + num + " parole = " + result);
                    }catch(RemoteException e) {
                        System.out.println("Errore: " + e.toString());
                    }
                    
                }else if(service.equals("E")) {
                    String[] split = stdIn.readLIne().split(" ");
                    String file = split[0];
                    int num = Integer.parseInt(split[1]);
                    
                        try{
                            int result = serverRMI.elimina_riga(file, num);
                            System.out.println("Elimina riga effettuata sul file + " + file + ": numero di righe rimaste = " + result);
                        }catch(RemoteException e) {
                            System.out.println("Errore: " + e.toString());
                        }
                    }
                    else System.out.println("Servizio non disponibile");
            }
            System.out.println("Servizio: (C -> conta righe) (D -> elimina riga)");

        }catch (Exception e) {
           System.out.println("Errore durante l'esecuzione");
        }
        
    }
 }

/* Creazione del .class: javac ClientRMI.java
   Esecuzione: java Client localhost [registry_port]
 */
