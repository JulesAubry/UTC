<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Modification projet</title>
  </head>
  <body>
  	<a href="index.php">Index</a><br>
  	<?php

		if(isset($_POST) && isset($_POST['code'])){
			$code = $_POST['code']; 
			$select = "SELECT * FROM projet WHERE code = $code"; //begin archive projet apres modif
			$exeArchive = pg_query($connexion, $select); //
			$resultArchive = pg_fetch_assoc($exeArchive);
			$titreArch = $resultArchive['titre'];
			$descriptionArch = $resultArchive['description'];
			$avantArch = $resultArchive['en_avant'];
			$selectArchive = "SELECT * FROM projet_archive WHERE code = $code";
			$existArchive = pg_query($connexion, $selectArchive);
			if (pg_num_rows($existArchive) == 0) {
			   $archiveQuery = "INSERT INTO projet_archive (numero_archive, code, titre, description, en_avant) VALUES (
				2, '$code', '$titreArch', '$descriptionArch', '$avantArch')"; //archive projet
			 } 
			 else {
			 	$archiveQuery = "UPDATE projet_archive SET titre='$titreArch', description='$descriptionArch', en_avant='$avantArch'
						WHERE code=$code"; //archive projet
			 }
			$query = "DELETE FROM projet WHERE code=$code";
			$exe = pg_query($connexion, $query);
			$archiveResult = pg_query($connexion, $archiveQuery); //end archive projet
			if($exe&&$archiveResult){
				?>
				<div>
					Suppression effectuée ! 
				</div>
				<?php
			}
			
		}

	?>

  </body>
  </html>	

