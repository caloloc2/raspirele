<?php 

// Funcion que escribe en el archivo configurado el dato de la hora recibida
function Escribe($dato){
	$fp = fopen("hora.rsp", "w");
	fputs($fp, $dato);
	fclose($fp);
}

if (isset($_POST['hora'])){	 // comprueba que llega un dato desde la aplicacion
	$data['respuesta'] = "Los reles se activarán a las ".$_POST['hora']; // crea un mensaje que saldra en la aplicacion.
	Escribe($_POST['hora']); // Envia a la funcion el dato de la hora recibida
	$respuesta[] = $data;
}else{	
	$data['respuesta'] = "Error al configurar hora."; // crea el mensaje de error en caso de haberlo.
	Escribe(""); // manda vacio a la funcion para que no se guarde ninguna hora.
	$respuesta[] = $data;
}

echo json_encode($respuesta); // envia el resultado a la aplicacion