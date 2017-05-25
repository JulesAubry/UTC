<?php 
header('Content-type: image/jpg');

$connexion = pg_connect("host='tuxa.sme.utc' port='5432' dbname='dbnf17a017' user='nf17a017' password='uWqde1BR'");

if(isset($_GET['img']) && isset($_GET['code'])){
	$img = $_GET['img'];
	$code = $_GET['code'];
	$q = "SELECT $img FROM projet WHERE code=$code";
	$r = pg_query($connexion, $q);
	$r = pg_fetch_assoc($r);
	$r = $r[$img];
	echo pg_unescape_bytea($r);
}