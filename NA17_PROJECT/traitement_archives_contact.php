<?php
	include("connexion.php");
	if(isset($_GET['t'])){
		if($_GET['t'] == 'pm'){
			echo "Restauration d'une personne morale<br \>";
			$id = $_POST['id'];
			$query1 = "SELECT count(id) FROM personne_morale WHERE id='$id' ;";
			$exec1 = pg_query($connexion, $query1);
			if($exec1){
				/* Récupération des données dans la table d'archivage */
				$query2 = "SELECT email, nom, type FROM personne_morale_archive WHERE numero_archive = '$id';";
				$exec2 = pg_query($connexion, $query2);
				$result2 = pg_fetch_assoc($exec2);
				$email = $result2['email'];
				$nom = $result2['nom'];
				$type = $result2['type'];
				/* Direction vers une nouvelle insertion (la personne a été supprimé) ou vers une modification (la personne a été modifiée */
				$result1 = pg_fetch_assoc($exec1);
				if($result1['count'] == 1){ // Cas où la personne est déjà présente dans la table non archive
					$query3 = "UPDATE personne_morale SET email = '$email', nom = '$nom', type = '$type' WHERE id='$id';";
					$exec3 = pg_query($connexion, $query3);
				}else{ // Cas où la personne n'est plus présente dans la table non archive
					$query4 = "INSERT INTO personne_morale (email, nom, type) VALUES ('$email', '$nom', '$type');";
					$exec4 = pg_query($connexion, $query4);					
				}
				$query5 = "DELETE FROM personne_morale_archive WHERE numero_archive = '$id'";
				$exec5 = pg_query($connexion, $query5);	
				echo "La personne morale a bien été restauré. Cliquez <a href='archives.php'>ici</a> pour retourner aux archives";
			}
		}
		if($_GET['t'] == 'pp'){
			echo "Restauration d'une personne physique<br \>";
			$id = $_POST['id'];
			echo $id;
			$query1 = "SELECT count(id) FROM personne_physique WHERE id='$id' ;";
			$exec1 = pg_query($connexion, $query1);
			if($exec1){
				/* Récupération des données dans la table d'archivage */
				$query2 = "SELECT email, nom, prenom FROM personne_physique_archive WHERE numero_archive = '$id';";
				$exec2 = pg_query($connexion, $query2);
				$result2 = pg_fetch_assoc($exec2);
				$email = $result2['email'];
				$nom = $result2['nom'];
				$prenom = $result2['prenom'];
				/* Direction vers une nouvelle insertion (la personne a été supprimé) ou vers une modification (la personne a été modifiée */
				$result1 = pg_fetch_assoc($exec1);
				if($result1['count'] == 1){ // Cas où la personne est déjà présente dans la table non archive
					$query3 = "UPDATE personne_physique SET email = '$email', nom = '$nom', prenom = '$prenom' WHERE id='$id';";
					$exec3 = pg_query($connexion, $query3);
				}else{ // Cas où la personne n'est plus présente dans la table non archive
					$query4 = "INSERT INTO personne_physique (email, nom, prenom) VALUES ('$email', '$nom', '$prenom');";
					$exec4 = pg_query($connexion, $query4);					
				}
				$query5 = "DELETE FROM personne_physique_archive WHERE numero_archive = '$id'";
				$exec5 = pg_query($connexion, $query5);	
				echo "La personne physique a bien été restauré. Cliquez <a href='archives.php'>ici</a> pour retourner aux archives";
			}
		}
	}
?>
