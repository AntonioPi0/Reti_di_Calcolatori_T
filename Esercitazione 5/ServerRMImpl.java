
/**
 * ServerRMImpl.java
 * Implementazione del server
 **/

import java.io.*;
import java.rmi.*;
import java.rmi.server.*;


public class ServerRMImpl extends UnicastRemoteObject implements ServerRMI {

	// Costruttore
	public ServerRMImpl() throws RemoteException{
		super();
	}

	// metodo conta_righe
	public int conta_righe(String file, int num) throws RemoteException {
		// il metodo conta le righe che hanno un numero di parole maggiore di num.
		// In quel caso incrementa un contatore che verrà resituito come output della funzione.

		int x, countline = 0, wordcount = 0;
		char ch, prev = ' ';

		FileReader in = null;

		try{
			in = new FileReader(file);
		}catch(FileNotFoundException e) {
			throw new RemoteException(e.toString());
		}

		try{
		while((x = in.read()) >= 0) {
					ch = (char) x;

					if(ch == '\n'){
						if(wordcount > num) countline++;
						wordcount = 0;
					}	
					else{
						if(ch == ' ' || ch == '\r'){
							if(prev == ' ' || prev == '\r' || prev == '\n');
							else wordcount++;
						}
					}
					prev = ch;
				}	
		}catch(IOException e) {
			throw new RemoteException(e.toString());
		}

		try{
			in.close();
		}catch (IOException e) {
			throw new RemoteException(e.toString());
		}
		return countline;
	}

	public int elimina_riga(String file, int num) throws RemoteException {
		FileReader reader = null;
		String outname = file.substring(0,file.length()-4) + "_modificato.txt";
		File in,out;
		BufferedReader buff;
		FileWriter writer = null;

		try{
			in = new File(file);
			out = new File(outname);
			reader = new FileReader(file);
			buff = new BufferedReader(reader);
			writer = new FileWriter(out);
		}catch (FileNotFoundException e) {
			throw new RemoteException(e.toString());
		} catch (IOException e) {
			throw new RemoteException(e.toString());
		}

		
		String line;
		int countline = 0;
		
		try{
			while((line = buff.readLine()) != null) {
			countline++;

			if(countline != num) 
				writer.write(line + "\n");

			}

			buff.close();
			writer.close();

			in.delete();
			out.renameTo(in);
		}catch(IOException e) {
			throw new RemoteException(e.toString());
		}

		if (countline < num) {
			throw new RemoteException(
					"Il file remoto scelto ha " + countline+ " righe. Inserire un numero minore di " + num);
		} else {
			return countline - 1;
		}
	}

	// Avvio del Server RMI
	public static void main(String[] args) {
		
		int REGISTRYPORT = 1099;
		String registryHost = "localhost";
		String serviceName = "ServerCongresso"; // lookup name...

		if (args.length != 0 && args.length != 1) {
			System.out.println("Sintassi: ServerImpl [registryPort]");
			System.exit(1);
		}
		if (args.length == 1) {
			try {
				REGISTRYPORT = Integer.parseInt(args[0]);
			} catch (Exception e) {
				System.out.println("Sintassi: ServerImpl [registryPort], registryPort intero");
				System.exit(2);
			}
		}
		
		// Registrazione del servizio RMI
		String completeName = "//" + registryHost + ":" + REGISTRYPORT + "/" + serviceName;
		try {
			ServerRMImpl serverRMI = new ServerRMImpl();
			Naming.rebind(completeName, serverRMI);
			System.out.println("Server RMI: Servizio \"" + serviceName + "\" registrato");
		} catch (Exception e) {
			System.err.println("Server RMI \"" + serviceName + "\": " + e.getMessage());
			e.printStackTrace();
			System.exit(1);
		}
	}
}
