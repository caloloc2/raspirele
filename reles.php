<?php 


// Funcion que escribe el dato de que rele encender segun se reciba desde la aplicacion
function Escribe($dato){
	$fp = fopen("estados.rsp", "w");
	fputs($fp, $dato);
	fclose($fp);
}

$rele = 0;


if ((isset($_POST['rele']))&&(isset($_POST['estado']))){ // comprueba que llegue la informacion
	$data['valor'] = 1;
	$rele = $_POST['rele'];
	if ($_POST['estado']=='1'){ // activa cualquier rele
		if ($rele == '1'){ // activa rele 1
			Escribe('2');
		}else{ // activa rele 2
			Escribe('4');
		}
		$data['respuesta'] = "Activando Rele ".$rele; // crea mensaje para la aplicacion
	}else{ // desactiva cualquier ele
		if ($rele == '1'){ // desactiva rele 1
			Escribe('1');
		}else{ // desactiva rele 2
			Escribe('3');
		}
		$data['respuesta'] = "Desactivando Rele ".$rele; // crea mensaje para la aplicacion
	}

	$respuesta[] = $data;	
}else{
	$data['valor'] = $rele;
	$data['respuesta'] = "Error al activar reles."; // crea mensaje en caso de error

	$respuesta[] = $data;	
}

echo json_encode($respuesta); // envia respuesta a la aplicacion
