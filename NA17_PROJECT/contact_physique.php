<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="utf-8">
		<title>Modification contact</title>
	</head>
	<body>
  		<a href="index.php">Index</a><br><form action='traitement_ajouter_contact.php?t=p' method='post'><br \><br \>
		<label for='nom'>Nom : </label><input type='text' id='nom' name='nom' maxlength='20' required/><br \><br \>
		<label for='prenom'>Prénom : </label><input type='text' id='prenom' name='prenom' maxlength='20' required/><br \><br \>
		<label for='employeur'>Employeur : </label>

		<?php
			$query2 = "SELECT id, email FROM personne_morale";
			$exec2 = pg_query($connexion, $query2);
			if($exec2){
				echo "<select name='employeur' id='employeur'>";
				while($result2 = pg_fetch_assoc($exec2)){
					
					echo "<option value='".$result2['id']."'>".$result2['email']."</option>";
				}
				echo "</select><br \><br \>";
			}
		?>
		<label for='mail'>M@il : </label><input type='email' id='mail' name='mail' maxlength='320' /><br \><br \>
		<label for='titre'>Poste : </label><input type='text' id='poste' name='poste' maxlength='50'/><br \><br \>
		<input type='submit' value='Ajouter' />
		</form>
	</body>
</html>
