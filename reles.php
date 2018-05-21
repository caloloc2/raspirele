<?php 

function Escribe($dato){
	$fp = fopen("estados.rsp", "w");
	fputs($fp, $dato);
	fclose($fp);
}

$rele = 0;

if ((isset($_POST['rele']))&&(isset($_POST['estado']))){
	$data['valor'] = 1;
	$rele = $_POST['rele'];
	if ($_POST['estado']=='1'){ // activa
		if ($rele == '1'){
			Escribe('2');
		}else{
			Escribe('4');
		}
		$data['respuesta'] = "Activando Rele ".$rele;
	}else{ // desactiva
		if ($rele == '1'){
			Escribe('1');
		}else{
			Escribe('3');
		}
		$data['respuesta'] = "Desactivando Rele ".$rele;
	}

	$respuesta[] = $data;	
}else{
	$data['valor'] = $rele;
	$data['respuesta'] = "Error al activar reles.";

	$respuesta[] = $data;	
}

echo json_encode($respuesta);
