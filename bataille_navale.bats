setup() {
    load 'bats/bats-support/load'
   	load 'bats/bats-assert/load'
}

prog=bataille_navale

@test "Test 1: Entrée avec deuxième argument invalide" {
    run ./$prog -C stats.txt
    assert_output --partial "Erreur: Argument invalide."
    assert_failure 1
}

@test "Test 2: Entrée avec -S sans fichier de sortie" {
    run ./$prog -S
    assert_output --partial "Erreur: Veuillez entrer un fichier de sortie."
    assert_failure 1
}

@test "Test 3: Entrée avec plus de deux arguments" {
    run ./$prog -S arg2 arg3
    assert_output --partial "Erreur"
    assert_failure 1
}

@test "Test 4: Entrée avec plus de deux arguments" {
    run ./$prog -S arg2 arg3
    assert_output --partial "- Pour simplement exécuter ce logiciel, veuillez entrer "
    assert_failure 1
}
