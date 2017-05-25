<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Association projet - personne</title>
  </head>
  <body>
  	<a href="index.php">Index</a><br \><br \>
	Associer une personne physique : <br \>
	<form action="traitement_associer_personne.php?p=p" method="post">
	  	<?php
			if(isset($_GET) && isset($_GET['id'])){
				$code = $_GET['id']; 
				echo "<input type='hidden' name='projet' value='$code' />";
				$query1 = "SELECT id, nom, prenom FROM personne_physique WHERE id NOT IN (SELECT id_contact FROM a_pour_role WHERE code = '$code');";
				$exec1 = pg_query($connexion, $query1);
				if($exec1){
					echo "<select name='personne_physique' id='personne_physique'>";
					while($result = pg_fetch_assoc($exec1)){
						echo "<option value='".$result['id']."'>".$result['nom']." ".$result['prenom']."</option>";
					}
					echo "</select><br \><br \>";
				
				}
			}
		?>
		<label for="titre">Rôle : </label>
		<input type="text" id="role" name="role" maxlength='20'/><br \><br \>
		
		<input type="submit" value="Associer" />
	</form><br \><br \>
	Associer une personne morale :<br \>
	<form action="traitement_associer_personne.php?p=m" method="post">
	  	<?php
			if(isset($_GET) && isset($_GET['id'])){
				$code = $_GET['id']; 
				echo "<input type='hidden' name='projet' value='$code' />";
				$query2 = "SELECT id, nom, type FROM personne_morale WHERE id NOT IN (SELECT id_contact FROM a_pour_role WHERE code = '$code');";
				$exec2 = pg_query($connexion, $query2);
				if($exec2){
					echo "<select name='personne_morale' id='personne_morale'>";
					while($result2 = pg_fetch_assoc($exec2)){
						echo "<option value='".$result2['id']."'>".$result2['type']." ".$result2['nom']."</option>";
					}
					echo "</select><br \><br \>";
				
				}
			}
		?>
		<label for="titre">Rôle : </label>
		<input type="text" id="role" name="role" maxlength='20' /><br \><br \>
		
		<input type="submit" value="Associer" />
	</form><br \><br \>
  </html>

