<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Projet</title>
  </head>
  <body>

		<a href="index.php">Index</a>

		<?php 
				$envoi = NULL;
				// Vide la base de projets
				//include("nettoyage_projet.php");
			if(isset($_POST) && isset($_POST["titre"])){
				$envoi = "truc";
				$code = $_POST["code"];
				$titre = $_POST["titre"];
				$description = $_POST["description"];
				if(isset($result['p_date']))
					$date = $result['p_date'];
				else $date = date("Y-m-d", time());	
				$avant = $_POST["avant"];
				if($avant == "on") $avant = "true"; else $avant = "false";
				if(isset($_POST["modif"])){
					$modif = $_POST["modif"];
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
						1, '$code', '$titreArch', '$descriptionArch', '$avantArch')"; //archive projet
					 } 
					 else {
					 	$archiveQuery = "UPDATE projet_archive SET titre='$titreArch', description='$descriptionArch', en_avant='$avantArch'
								WHERE code=$code"; //archive projet
					 }
					$archiveResult = pg_query($connexion, $archiveQuery); //end archive projet
					$query = "UPDATE projet SET titre='$titre', description='$description', p_date='$date', en_avant='$avant'
								WHERE code=$code";
					$result = pg_query($connexion, $query);
				}
				else $modif = NULL;
				$rd = "readonly='true'";
				$en = "enable='false'";
				if($modif != "t"){
					$query = "INSERT INTO projet (titre, description, en_avant) VALUES ('$titre', '$description', $avant)";
					$exec = pg_query($connexion, $query); 
				}
				if($exec || ($modif == "t" && $result) || $archiveResult){
					if($avant == "true") $avant = "checked"; else $avant = "";
					?>
					<div>
						<span>Action réussie !<span><br><br>
						<span>Récap</span>
					</div>
					<?php
				}
				else{
					?>
					<div>
						<span>Erreur - Action non effectuée.</span>
					</div>
					<?php
				}
			}
			
			if(isset($result['p_date']))
				$date = $result['p_date'];
			else $date = date("Y-m-d", time());	
		?>

		<div>
			<form action="" method="post">
				<ul>
					<li>
						<label for="titre">Titre</label>
						<input type="text" id="titre" name="titre" value="<?php echo $titre; ?>" required <?php echo $rd;?> />
					</li>
					<li>
						<label for="description">Description</label>
						<input type="text" id="description" name="description" value="<?php echo $description; ?>" required <?php echo $rd;?>/>
					</li>
					<li>
						<label for="date">Date</label>
						<input type="text" id="date" name="date" value="<?php echo $date; ?>" required <?php echo $rd;?>/>
					</li>
					<li>
						<label for="avant">Mettre en avant ?</label>
						<input type="checkbox" id="avant" name="avant" <?php echo $avant . ' ' . $en;?> />
					</li>
					<?php 
					if($modif != "t" && $envoi != "truc"){ // si on ne se situe pas dans un cas d'affichage, on permet l'envoi de données
					?>
					<li>
						<input type="submit" value="Envoi" />
					</li>
					<?php
					}
					?>
				</ul>
			</form>
		</div>
  </body>
</html>

<!--
	creer projet
	contact 
	modele
	editer chaque élément créé 

	-->
