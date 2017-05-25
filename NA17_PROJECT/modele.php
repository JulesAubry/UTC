<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Modele</title>
  </head>
  <body>
		<div>
			<table>
				<th> Numero de modele</th>
				<th> Version </th>

		<a href="index.php">Index</a>
		
		<?php	
		
				$vSql ="SELECT * FROM modele_scenari";
				$vQuery=pg_query($connexion, $vSql);

				while ($vResult = pg_fetch_array($vQuery, null, PGSQL_ASSOC)) { 

				$int1 = 0;

				$vSql2 ="SELECT n_skin FROM skin WHERE modele = {$vResult['nom_modele']} AND version = '{$vResult['n_vers']}'";
				$vSql3 ="SELECT n_extension FROM extension WHERE modele = {$vResult['nom_modele']} AND version = '{$vResult['n_vers']}'";
				
				$vQuery2=pg_query($connexion, $vSql2);				
				$vQuery3=pg_query($connexion, $vSql3);
				
				echo "<tr> <td> {$vResult['nom_modele']} </td> <td>  {$vResult['n_vers']}</td> <td> skin : </td>";
				while ($vResult2 = pg_fetch_array($vQuery2, null, PGSQL_ASSOC)) { 	
						echo "<td> {$vResult2['n_skin']}</td>";
				}
				echo "</tr> <tr> <td></td><td></td> <td> extension : </td>";
				while ($vResult3 = pg_fetch_array($vQuery3, null, PGSQL_ASSOC)) { 	
						echo "<td> {$vResult3['n_extension']}</td>";
						$int1 = $int1 + 1; 
				}
				while($int1 < 10) {
					echo "<td> </td>";
					$int1 = $int1 + 1;
				}	
				echo " <td > <form action=\"supp_modele.php?nom={$vResult['nom_modele']}&vers={$vResult['n_vers']}\" method=\"POST\"> <input type=\"submit\" value=\"SUPPRIMER\" /> </form> </td>";							
				
		} ?>
			</table>
		</div>
		
		</br></br></br>
		
		<h2> Les SKINS </h2>
		
		<div>
			<table>
				<th> Skin</th>
		<?php	
		
				$vSql ="SELECT DISTINCT n_skin FROM SKIN";
				$vQuery=pg_query($connexion, $vSql);
				echo "<tr>";
				while ($vResult = pg_fetch_array($vQuery, null, PGSQL_ASSOC)) { 
				echo "<td> {$vResult['n_skin']} </td>";
				
				}
				echo "</tr>";			
				
		?>
			</table>
		</div>
		
			</br></br></br>
			
		<h2> Les EXTENSIONS </h2>
			
		<div>
			<table>
				<th> Extension</th>
		<?php	
		
				$vSql ="SELECT DISTINCT n_extension FROM extension";
				$vQuery=pg_query($connexion, $vSql);
				echo "<tr>";
				while ($vResult = pg_fetch_array($vQuery, null, PGSQL_ASSOC)) { 
				echo "<td> {$vResult['n_extension']} </td>";
				
				}
				echo "</tr>";
				
		?>
			</table>
		</div>

			</br></br></br>
			
		<div> 	
			<h2> Ajout d'un modele : </h2>
				<form action="ajout_modele.php" method="post">
				<ul>
					<li>
						<label for="titre"> Nom modele </label>
						<input type="number" id="nom" name="nom"> </input>
					</li>
					<li>
						<label for="titre"> Numero version </label>
						<input type="number" id="vers" name="vers" step="0.1"> </input>
					</li>
					<li>
						<label for="titre"> Skin </label>
						<input type="text" id="skin" name="skin"> </input> de la forme  : "skin1,skin2,skin3,..."
					</li><li>
						<label for="titre"> Extension </label>
						<input type="text" id="extension" name="extension"> </input> de la forme  : "extension1,extension2,extension3,..."
					</li>
					<input type="submit"></input>
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
