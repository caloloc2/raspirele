<?php 

if (isset($_POST['hora'])){	
	$data['respuesta'] = "Los reles se activarán a las ".$_POST['hora'];
	$respuesta[] = $data;
}else{	
	$data['respuesta'] = "Error al configurar hora.";
	$respuesta[] = $data;
}

echo json_encode($respuesta);