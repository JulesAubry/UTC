<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Gestion archives</title>
  </head>
  <body>
  	<a href="index.php">Index</a><br>
	<h2>Archives personnes morales</h2>
	<table><tr><th>Em@il</th><th>Nom</th><th>Type</th><th>Restaurer</th></tr>
  	<?php
		$query1 = "SELECT numero_archive, email, nom, type FROM personne_morale_archive;";
		$exec1 = pg_query($connexion, $query1);
		if($exec1){
			while($result1 = pg_fetch_assoc($exec1)){
				echo "<tr><td>".$result1['email']."</td><td>".$result1['nom']."</td><td>".$result1['type']."</td>";
				echo "<td><form action='traitement_archives_contact.php?t=pm' method='post'><input type='hidden' value='".$result1['numero_archive']."' id='id' name='id' /><input type='submit' value='Restaurer' /></form></td>";
				echo "</tr>";
			}
		}
	?>
	</table>
	<hr>
	<h2>Archives personnes physiques</h2>
	<table><tr><th>Em@il</th><th>Nom</th><th>Prénom</th><th>Restaurer</th></tr>
  	<?php
		$query2 = "SELECT numero_archive, email, nom, prenom FROM personne_physique_archive;";
		$exec2 = pg_query($connexion, $query2);
		if($exec2){
			while($result2 = pg_fetch_assoc($exec2)){
				echo "<tr><td>".$result2['email']."</td><td>".$result2['nom']."</td><td>".$result2['prenom']."</td>";
				echo "<td><form action='traitement_archives_contact.php?t=pp' method='post'><input type='hidden' value='".$result2['numero_archive']."' id='id' name='id' /><input type='submit' value='Restaurer' /></form></td>";
				echo "</tr>";
			}
		}
	?>
	</table>
	<hr>
	<h2>Archives des modèles</h2>
	<table><tr><th>Numero de modèle</th> <th> </th> <th> Version </th></tr>
  	<?php
		$query3 = "SELECT DISTINCT numero_archive, version FROM modele_scenari_archive WHERE numero_archive NOT IN (SELECT nom_modele FROM modele_scenari) AND version NOT IN (SELECT n_vers FROM modele_scenari) ;";
		$exec3 = pg_query($connexion, $query3);
		$nbArchives = 0;
		if($exec3){
			while($result3 = pg_fetch_assoc($exec3)){
				$nbArchives++;
				echo "<tr><td>".$result3['numero_archive']."</td><td> <td>".$result3['version']."</td><td></td>";
				echo "<td><form action='restaurer_archive_modele.php' method='GET'><input type='hidden' value='".$result3['numero_archive']."' id='id' name='nom' /><input type='hidden' value='".$result3['version']."' id='id' name='vers' /><input type='submit' value='Restaurer' /></form></td>";
				echo "</tr> Pensez à supprimer une archive avant d'en restaurer une ayant le meme nom";
			}
		}
	?>
	</table>
	<?php if ($nbArchives ==0) {
		echo "Désolé mais il n'y a pas d'archives de modèles à restaurer ! </br></br>";
	}
?>

	<hr>
	<h2>Archives des projets</h2>
	<table><tr><th>code</th><th>titre</th><th>description</th><th>date</th><th>image1</th><th>image2</th><th>image3</th></tr>
  	<?php
		$query4 = "SELECT numero_archive, code, titre, description, p_date, image1, image2, image3 FROM projet_archive;";
		$exec4 = pg_query($connexion, $query4);
		if($exec4){
			while($result4 = pg_fetch_assoc($exec4)){
				$code = $result4['code'];
				echo "<tr><td>".$result4['code']."</td><td>".$result4['titre']."</td><td>".$result4['description']."</td><td>".$result4['p_date']."</td>";
				echo "<td><img src='apercu.php?img=image1&code=$code' height='50' width='50'/></td>";
				echo "<td><img src='apercu.php?img=image2&code=$code' height='50' width='50'/></td>";
				echo "<td><img src='apercu.php?img=image3&code=$code' height='50' width='50'/></td>";
				echo "<td><form action='traitement_archives_projet.php' method='post'><input type='hidden' value='".$result4['code']."' id='id' name='code' /><input type='submit' value='Restaurer' /></form></td>";
				echo "</tr>";
			}
		}
	?>
	</table>
  </body>
  </html>	

