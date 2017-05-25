<?php
	include("connexion.php");
	if(isset($_POST)){
		$id = $_POST['id']; // id du projet
		$lien = $_POST['lien']; // url vers le forum ou un autre projet
		$typelien = $_POST['typelien']; // Contient F (forum) ou P (projet)
		
		$query2 = "SELECT code FROM lien WHERE url= '$lien' ;";
		$exec2 = pg_query($connexion, $query2);
		if($exec2){
			$result2 = pg_fetch_assoc($exec2);
			if($result2['code'] == NULL){
				$query = "INSERT INTO lien(url, code, type) VALUES('".$lien."', ".$id.", '".$typelien."')";
				$exec = pg_query($connexion, $query);
				echo "Insertion effectuée avec succés. <a href='index.php'>Retourner</a> sur la page index.";
			}else{
				echo "Ce lien référence déjà  un autre projet ! <a href='index.php'>Retourner</a> sur la page index.";
			}
		}
	}
?>

<!-- Avec type = F ou P-->
