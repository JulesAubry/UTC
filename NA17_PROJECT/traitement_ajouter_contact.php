<?php
	include("connexion.php");
	if(isset($_GET['t'])){
		if($_GET['t'] == 'p'){ // Personne physique
			$nom = str_replace("'", "", $_POST['nom']);
			$prenom = str_replace("'", "", $_POST['prenom']);
			$employeur = str_replace("'", "", $_POST['employeur']);
			$mail = str_replace("'", "", $_POST['mail']);
			$poste = str_replace("'", "", $_POST['poste']);
			$query2 = "INSERT INTO personne_physique(email, employeur, nom, prenom, poste) VALUES('".$mail."', '".$employeur."', '".$nom."', '".$prenom."', '".$poste."') RETURNING id;";
			$exec2 = pg_query($connexion, $query2);
			if(!exec2)
				echo "Erreur lors de l'enregistrement. Veuillez réessayer";
			else{
				$result = pg_fetch_assoc($exec2);
				$id = $result['id'];
				echo "Personne physique modifiée, <a href='modifier_contact.php?t=p&c=".$id."'>retourner</a> à la page du contact";
			}
			
		}
		if($_GET['t'] == 'm'){ // Personne morale
			$mail = str_replace("'", "", $_POST['mail']);
			$nom = str_replace("'", "", $_POST['nom']);
			$type = str_replace("'", "", $_POST['type']);
			$query1 = "INSERT INTO personne_morale(email, nom, type) VALUES('".$mail."', '".$nom."', '".$type."') RETURNING id;";
			$exec1 = pg_query($connexion, $query1);
			if(!$exec1)
				echo "Erreur lors de l'enregistrement. Veuillez réessayer";
			else{
				$result = pg_fetch_assoc($exec1);
				$id = $result['id'];
				echo "Personne morale modifiée, <a href='modifier_contact.php?t=m&c=".$id."'>retourner</a> à la page du contact";
			}
		}
	}
?>
