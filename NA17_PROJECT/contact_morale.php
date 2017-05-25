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
		<a href="index.php">Index</a><br \><br \>
		<form action='traitement_ajouter_contact.php?t=m' method='post'>
		<label for='nom'>Email : </label><input type='email' id='mail' name='mail' maxlength='320' /><br \><br \>
		<label for='nom'>Nom : </label><input type='text' id='nom' name='nom' maxlength='20' required /><br \><br \>
		<label for='nom'>Type : </label><input type='text' id='type' name='type' maxlength='10' /><br \><br \>
		<input type='submit' value='Ajouter' />
		</form>
	</body>
</html>
