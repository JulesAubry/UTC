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
			$select = "SELECT * FROM projet WHERE code = $code";
			$exe = pg_query($connexion, $select);
			if($exe){
				$result = pg_fetch_assoc($exe);
				if(isset($result['p_date']))
					$date = $result['p_date'];
				else $date = date("Y-m-d", time());	
				if($result['en_avant'] == 't') $avant = 'checked'; else $avant = '';
				?>
				<div>
					<form action="projet.php" method="post">
					<ul>
						<li>
							<label for="titre">Titre</label>
							<input type="textarea" id="titre" name="titre" value="<?php echo $result['titre'];?>" required />
						</li>
						<li>
							<label for="description">Description</label>
							<input type="textarea" id="description" name="description" value="<?php echo $result['description'];?>" required />
						</li>
						<li>
							<label for="date">Date </label>
							<input type="date" id="date" name="date" value="<?php echo $date;?>" required />
						</li>
						<li>
							<label for="avant">Mettre en avant ?</label>
							<input type="checkbox" id="avant" name="avant" <?php echo $avant; ?>/>
						</li>
							<input type="hidden" name="modif" value="t" />
							<input type="hidden" name="code" value="<?php echo $code;?>" />
						<li>
							<input type="submit" value="Envoi" />
						</li>

						<li>
							<a href="image.php?code=<?php echo $code;?>"><input type="button" value="Image" /></a>
						</li>
					</ul>
				</form>
			</div>
			<div>
				<?php
					$q = "SELECT * FROM associe_a WHERE code1 = $code OR code2 = $code";
					$r =  pg_query($connexion, $q);
					$nombre = pg_num_rows($r);
					if($nombre == 0) $phrase = "Ce projet n'est lié à aucun autre projet.<br>";
					else $phrase = "Ce projet est lié à $nombre autres projets : <br>";
					echo $phrase;
					// boucle sur les autres projets
					if($nombre > 0){
						while($res = pg_fetch_assoc($r)){
							// on récupère le code de l'autre projet
							if($res['code1'] != $code)
								$num = $res['code1'];
							else $num = $res['code2'];
							// on va chercher son titre
							$query = "SELECT titre FROM projet WHERE code=$num";
							$resultat = pg_query($connexion, $query);
							$resultat = pg_fetch_assoc($resultat);
							$nom = $resultat["titre"];
							echo "- $nom <br>";
						}
					}
					echo "<a href='associer_projet.php?id=".$code."'><span>Associer un projet à ce projet</span></a><br \><br \>";

			}
			/* Association entre un projet et un contact */
				$pers_phy = 1;
				$query1 = "SELECT a.id_contact, a.role, p.nom FROM a_pour_role a INNER JOIN personne_physique p ON a.id_contact = p.id WHERE code = '$code';";
				$exec1 = pg_query($connexion, $query1);
				while($result1 = pg_fetch_assoc($exec1)){
					if($pers_phy == 1){
						echo "Ce projet est lié au(x) personne(s) physique(s) suivante(s) :<br \>";
						$pers_phy = 0;
					}
					echo "- ".$result1['nom']." (".$result1['role'].")<br \>";
				}
				$pers_mor = 1;
				$query2 = "SELECT a.id_contact, a.role, m.nom FROM a_pour_role a INNER JOIN personne_morale m ON a.id_contact = m.id WHERE code = '$code';";
				$exec2 = pg_query($connexion, $query2);
				while($result2 = pg_fetch_assoc($exec2)){
					if($pers_mor == 1){
						echo "Ce projet est lié au(x) personne(s) morale(s) suivante(s) :<br \>";
						$pers_mor = 0;
					}
					echo "- ".$result2['nom']." (".$result2['role'].")<br \>";
				}				
				echo "<a href='associer.php?id=".$code."'>Nouveau contact (physique ou morale)</a><br \><br \>";


			/*Association projet et modele */
			$selectNbAssociations = "SELECT nom_modele, n_vers FROM utilise WHERE code = $code ORDER BY 1";
			$querySelectNbAssociations =  pg_query($connexion, $selectNbAssociations);
			if(pg_num_rows($querySelectNbAssociations) > 0) {
				echo "Ce projet est lié aux modèles suivants : </br> ";
				while($v_Result = pg_fetch_array($querySelectNbAssociations, null, MYSQL_ASSOC)) {
					echo "- Modele : {$v_Result['nom_modele']} de version : {$v_Result['n_vers']}";
					echo "<form action=\"supprimer_association_projet_modele?id=$code&nom={$v_Result['nom_modele']}&vers={$v_Result['n_vers']}\" method=\"POST\"><input type=\"submit\" value=\"Supprimer cette association\"></form>";
				}
			}	
			echo "<a href='associer_projet_modele.php?id=".$code."'><span>Associer un modèle à ce projet</span></a> </br> </br>";
			


			/* Gestion des liens vers les forums et les projets */
				$lien = 1;
				$query3 = "SELECT url, type FROM lien WHERE code = '$code' ORDER BY type;";
				$exec3 = pg_query($connexion, $query3);
				while($result3 = pg_fetch_assoc($exec3)){
					if($lien == 1){
						echo "Ce projet est lié au(x) lien(s) suivant(s) : <br \>";
						$lien = 0;
					}
					echo "- ".$result3['url']." (";
					if($result3['type'] == 'F')
						echo "forum";
					else
						echo "projet";
					echo ")<br \>";
				}
				
				echo "<a href='lien.php?id=".$code."'>Ajouter un lien (vers un forum ou un projet)</a>";
		}

	?>
	</div>
</body>
</html>
