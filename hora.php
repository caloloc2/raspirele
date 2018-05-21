<?php 
function Escribe($dato){
	$fp = fopen("hora.rsp", "w");
	fputs($fp, $dato);
	fclose($fp);
}

if (isset($_POST['hora'])){	
	$data['respuesta'] = "Los reles se activarán a las ".$_POST['hora'];
	Escribe($_POST['hora']);
	$respuesta[] = $data;
}else{	
	$data['respuesta'] = "Error al configurar hora.";
	Escribe("");
	$respuesta[] = $data;
}

echo json_encode($respuesta);