/**
 * Interfaccia remota di servizio
 */

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.io.*;

public interface ServerRMI extends Remote {

	int conta_righe(String file, int num) throws RemoteException;

	int elimina_riga(String file, int num) throws RemoteException;
	
}

