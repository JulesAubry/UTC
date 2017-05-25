<?php
	include("connexion.php");
	require("functionsContact.php");
	if(isset($_GET['t'])){
		if($_GET['t'] == 'p'){ // Personne physique
			$code = $_POST['code'];
			$query1 = "DELETE FROM a_pour_role WHERE id_contact = '$code';"; // On vide la table a_pour_role concernant ce personnage physique
			$exec1 = pg_query($connexion, $query1);
			$query2 = "SELECT * FROM personne_physique WHERE id = '$code';";
			$exec2 = pg_query($connexion, $query2);
			$result2 = pg_fetch_assoc($exec2);
			$nom = $result2['nom'];
			$prenom = $result2['prenom'];
			$email = $result2['email'];
			// Création dans la table d'archivage
			archivagePersonnePhysique($code, $email, $nom, $prenom);
			$query5 = "DELETE FROM personne_physique WHERE id = '$code';";
			$query5 = pg_query($connexion, $query5);
			echo "Suppression d'une personne physique effectuée<br \>";
		}
		if($_GET['t'] == 'm'){ // Personne morale
			/* Récupération de l'id de la personne morale */
			$code = $_POST['code'];
			/* Suppression de toutes les relations a_pour_role avec cette personne morale */
			$query1 = "DELETE FROM a_pour_role WHERE id_contact = '$code';"; // On vide la table a_pour_role concernant ce personnage physique
			$exec1 = pg_query($connexion, $query1);
			/* Récupération des anciennes valeurs de la personne morale dans la BDD en vue de son archivage */
			$query2 = "SELECT * FROM personne_morale WHERE id = '$code';";
			$exec2 = pg_query($connexion, $query2);
			$result2 = pg_fetch_assoc($exec2);
			$nom = $result2['nom'];
			$type = $result2['type'];
			$email = $result2['email'];
			archivagePersonneMorale($code, $email, $nom, $type); // Fonction d'archivage
			

			/*$query6 = "DELETE FROM a_pour_role WHERE id_contact IN(SELECT id FROM personne_physique WHERE employeur = '$code');";
			$query6 = pg_query($connexion, $query6);*/
			$query7 = "UPDATE personne_physique SET employeur=NULL WHERE employeur = '$code';"; // On supprimer l'employeur des gens qui avait pour employeur la PM
			$query7 = pg_query($connexion, $query7);
			$query5 = "DELETE FROM personne_morale CASCADE WHERE id = '$code';";
			$query5 = pg_query($connexion, $query5);
			echo "Suppression d'une personne morale effectuée. Les personnesm morales qui avaient pour employeur cette personne physique n'ont désormais plus d'employeur<br \>";
		
		}
	}
	echo "Retourner à la page des <a href='contact.php'>contacts</a>.";
?>
