<?php
	function archivagePersonneMorale($num, $email, $nom, $type){
		include("connexion.php");
		$query1 = "SELECT * FROM personne_morale_archive WHERE numero_archive = '$num'";
		$exec1 = pg_query($connexion, $query1);
		if($exec1){
			$result = pg_fetch_assoc($exec1);
			if($result == NULL){ // Cas de l'insert
				$query2 = "INSERT INTO personne_morale_archive(numero_archive, email, nom, type) VALUES('".$num."', '".$email."', '".$nom."', '".$type."');";
				$exec2 = pg_query($connexion, $query2);
			}
			else{ // Cas de l'update
				$query3 = "UPDATE personne_morale_archive SET email = '".$email."',  nom = '".$nom."', type = '".$type."' WHERE numero_archive = '".$num."';";
				$exec3 = pg_query($connexion, $query3);
			}
		}
	}

	function archivagePersonnePhysique($num, $email, $nom, $prenom){
		include("connexion.php");
		$query1 = "SELECT * FROM personne_physique_archive WHERE numero_archive = '$num'";
		$exec1 = pg_query($connexion, $query1);
		if($exec1){
			$result = pg_fetch_assoc($exec1);
			if($result == NULL){ // Cas de l'insert
				$query2 = "INSERT INTO personne_physique_archive(numero_archive, email, nom, prenom) VALUES('".$num."', '".$email."', '".$nom."', '".$prenom."');";
				$exec2 = pg_query($connexion, $query2);
			}
			else{ // Cas de l'update
				$query3 = "UPDATE personne_physique_archive SET email = '".$email."',  nom = '".$nom."', prenom = '".$prenom."' WHERE numero_archive = '".$num."';";
				$exec3 = pg_query($connexion, $query3);
			}
		}
	}

?>
