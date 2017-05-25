<?php 
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Index</title>
  </head>
  <body>

	<a href="index.php">Index</a><br><br>
	<div>
		Créer un nouveau lien et l'ajouter à ce projet :<br \><br \>
		<form action='traitement_lien.php?t=add' method='post'>
		<?php
			if(isset($_GET['id']))
			{
				$id=$_GET['id'];
				echo "<input type='hidden' id='id' name='id' value='$id' />";

		?>
			Lien <input type='url' id='lien' name='lien' maxlength='50' required/><br \>
			Lien vers un forum  <input type="radio" name="typelien" value="F" id="F" checked /><br \>
			Lien vers un projet <input type="radio" name="typelien" value="P" id="P" /><br \>
			<input type='submit' value='Ajouter' /><br \><br \>
		</form>
		<?php
			}
		?>
	</div>
  </body>
</html>

