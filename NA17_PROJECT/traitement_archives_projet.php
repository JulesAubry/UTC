<?php
	include("connexion.php");
	echo "Restauration d'un projet<br \>";
	$code = $_POST['code'];
	$query1 = "SELECT count(*) FROM projet WHERE code='$code' ;";
	$exec1 = pg_query($connexion, $query1);
	if($exec1){
		/* Récupération des données dans la table d'archivage */
		$query2 = "SELECT code, titre, description, en_avant, p_date, image1, image2, image3 FROM projet_archive WHERE code = '$code';";
		$exec2 = pg_query($connexion, $query2);
		$result2 = pg_fetch_assoc($exec2);
		$titre = $result2['titre'];
		$description = $result2['description'];
		$en_avant = $result2['en_avant'];
		$p_date = $result2['p_date'];
		$image1 = $result2['image1'];
		$image2 = $result2['image2'];
		$image3 = $result2['image3'];
		/* Direction vers une nouvelle insertion (la personne a été supprimé) ou vers une modification (la personne a été modifiée */
		$result1 = pg_fetch_assoc($exec1);
		if($result1['count'] == 1){ // Cas où la personne est déjà présente dans la table non archive
			if(is_null($p_date)){
				$query3 = "UPDATE projet SET titre = '$titre', description = '$description', en_avant = '$en_avant', p_date = NULL, image1 = '$image1', image2 = '$image2', image3 = '$image3' WHERE code = $code;";
			}
			else {
				$query3 = "UPDATE projet SET titre = '$titre', description = '$description', en_avant = '$en_avant', p_date = '$p_date', image1 = '$image1', image2 = '$image2', image3 = '$image3' WHERE code = $code;";
			}
			$exec3 = pg_query($connexion, $query3);
		}else{ // Cas où la personne n'est plus présente dans la table non archive
			$query4 = "INSERT INTO projet (code, titre, description, en_avant, p_date, image1, image2, image3) VALUES (
						'$code', '$titre', '$description', '$en_avant','$p_date', '$image1', '$image2', '$image3')";
			$exec4 = pg_query($connexion, $query4);					
		}
		$query5 = "DELETE FROM projet_archive WHERE code = '$code'";
		$exec5 = pg_query($connexion, $query5);	
		echo "La projet a bien été restauré. Cliquez <a href='archives.php'>ici</a> pour retourner aux archives";
	}
?>