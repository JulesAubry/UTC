<?php
	include("connexion.php");
	if(isset($_GET['p'])){
		if($_GET['p'] == 'p'){ // Personne physique
			$code = $_POST['projet'];
			$contact = $_POST['personne_physique'];
			$role = $_POST['role'];
			$query1 = "INSERT INTO a_pour_role(code, id_contact, role) VALUES('$code', '$contact', '$role');";
			$exec1 = pg_query($connexion, $query1);

			echo "Association entre le projet et la personne physique créé avec succès<br \>";
		}
		if($_GET['p'] == 'm'){ // Personne morale
			$code = $_POST['projet'];
			$contact = $_POST['personne_morale'];
			$role = $_POST['role'];
			$query1 = "INSERT INTO a_pour_role(code, id_contact, role) VALUES('$code', '$contact', '$role');";
			$exec1 = pg_query($connexion, $query1);
			
			echo "Association entre le projet et la personne morale créé avec succès<br \>";
		}
	}
	echo "Retourner à la page des <a href='contact.php'>contacts</a>.";
?>
