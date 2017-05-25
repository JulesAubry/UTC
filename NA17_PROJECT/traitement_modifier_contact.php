<?php
	include("connexion.php");
	require("functionsContact.php");
	if(isset($_GET['t'])){
		if($_GET['t'] == 'p'){ // Personne physique
			/* Récupération des nouvelles valeurs et de l'id */
			$nom = str_replace("'", "", $_POST['nom']);
			$prenom = str_replace("'", "", $_POST['prenom']);
			$employeur = str_replace("'", "", $_POST['employeur']);
			$mail = str_replace("'", "", $_POST['mail']);
			$poste = str_replace("'", "", $_POST['poste']);
			$id = $_POST['id'];
			/* Sélection des anciennes valeurs dans la BDD */
			$query4 = "SELECT email, nom, prenom FROM personne_physique WHERE id ='$id';";
			$exec4 = pg_query($connexion, $query4);
			$result = pg_fetch_assoc($exec4);
			$ancien_email = $result['email'];
			$ancien_nom = $result['nom'];
			$ancien_prenom = $result['prenom'];
			/* Archivage dans la table d'archivage des personnes physiques */
			archivagePersonnePhysique($id, $ancien_email, $ancien_nom, $ancien_prenom);
			$query7 = "UPDATE personne_physique SET employeur = '$employeur', nom = '$nom', prenom = '$prenom', poste='$poste', email='$mail' WHERE id = '$id';";
			$exec7 = pg_query($connexion, $query7);
			/* Affichage et retour sur la page précédente */
			echo "Modification effectuée : <a href='modifier_contact.php?t=p&c=".$id."'>retourner</a> à la page des contacts";
		}
		if($_GET['t'] == 'm'){ // Personne morale
			/* Récupération des nouvelles valeurs et de l'id */
			$mail = str_replace("'", "", $_POST['mail']);
			$nom = str_replace("'", "", $_POST['nom']);
			$type = str_replace("'", "", $_POST['type']);	
			$id = $_POST['id'];
			/* Sélection des anciennes valeurs à archiver */
			$query4 = "SELECT email, nom, type FROM personne_morale WHERE id ='$id';";
			$exec4 = pg_query($connexion, $query4);
			$result = pg_fetch_assoc($exec4);
			$ancien_email = $result['email'];
			$ancien_nom = $result['nom'];
			$ancien_type = $result['type'];
			/* Archivage dans la table d'archivage des personnes morales dans la BDD */
			archivagePersonneMorale($id, $ancien_email, $ancien_nom, $ancien_type);
			$query7 = "UPDATE personne_morale SET nom = '$nom', type = '$type', email = '$mail' WHERE id = '$id';";
			$exec7 = pg_query($connexion, $query7);
			/* Affichage et rtour sur la page précédente */
			echo "Modification effectuée : <a href='modifier_contact.php?t=m&c=".$id."'>retourner</a> à la page des contacts";
		}
	}
	//header('Location: contact.php');
?>
