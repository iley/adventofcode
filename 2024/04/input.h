const char *sample[] = {
    "MMMSXXMASM", //
    "MSAMXMSMSA", //
    "AMXSXMAAMM", //
    "MSAMASMSMX", //
    "XMASAMXAMM", //
    "XXAMMXXAMA", //
    "SMSMSASXSS", //
    "SAXAMASAAA", //
    "MAMMMXMMMM", //
    "MXMXAXMASX", //
};

const char *input[] = {
    "ASAMXSMXMAXSAMMAMXAXXAXXMSAMXASAMXSASMSMXAXMAMMSSSMAMSMMSASMMSSMSMSMSXMMSX"
    "MXMAXXMAASMMMXMXMMXMAMXSSSMSMSMSMMMMAMMSMSXXAXMMXSAXMMXXAMASMXMASM",
    "MMXXAMXAXSMXMMSSMMSSMSMMXSSMXMAASASAAAAMSMSMSSXAMXXAMXAAAAMXASXAAAAAMASASA"
    "SMSSMMMSXSAMXAMAMSSMASAMAAAAAAXXAAXMAMXSAMAMSSMAMXMMSMMXSXAMAAASAS",
    "SAMMAXMSMXMAXMAMAAMXAAASAMXSXASAMAMMMXMMAXMAAXMXMMXSSSMMSXXMXMASMSMSMXMASA"
    "MAAXAAAMMSMMXMXAXAASAMAMMMSMSMSSSMSSXSAMSMMMAAMXXXAAAAAMAMSSSXMXAX",
    "AAMSAMMAMASXSMSMMMSMSMSMASAMMMMSMXMASXSSMSMMMSMSXAMXAASAMMMXSAMAAXAXMXMAMX"
    "MXXSXMMMAXASAAMSSSMMXSAMXAAXMAMXMAXAXMXAAXMMSSMMSMMSSSMAMMAAAMMMSM",
    "MMMSAXSMXMXAMAXXAXXAAXXMXMASMAAXXAXMSAAXSAXAAAASMSMMAMMXSAXAXAXMMMMMMXMASX"
    "MSMMXSAMMSAMMXMXAMXMAAXXMSMSMSMMMSMMXSMAMMSAAAXAASXXAMASXMMSMAAAMA",
    "XAAMAMXXSMMMMAMSSMMSMSXMXSXMMMXXMMSXMMMMSXSMSMXMAMMXAMMMMMMXMMMMMAXMAAMXSX"
    "AAAXAMAXMAMMMSSMSMAMASAMXAAAAAMXAAAXAXAASAXMSXMSSSMMMMAMAMXXXSMSSM",
    "SMSSXSXAAMMAMXXAMAMXXXAMMSAMXMXSMMAXMASXMAMAAAAAXXXSMSXASXMSXSAMSMSMMMSAXM"
    "ASMMXSXMASXAXAXAMSXSAXMSSMSMSMSMSSSMMMSXMASMAXAXMXMAAMSSSSMSAMAAMX",
    "XAMXAMMSMMSASMMASMMXMSSMAXAMASAAAXMMSASAMAMSMSMSAMXSAAMSMAAAAXXXAXAAMXMASX"
    "XMMAMXMSXMSXSMMMMXXMMSAAXXAXXASAAAXMSMMASXMXAAMMXXMMXMAAMAAMAMMMSS",
    "XSSMAMAXAASXXXSAMXMAXAAMSSSMAMXSMMSAMXSXSXXAAXAXMXAMMMSMSMMMSSSSMSSSMMMAMM"
    "AMSAMAMXAXSXSXMSAXXMAMMMMMMXMASXSMMXSAMAMSAMXSSSXMSSSMMSMMSMXMAAXA",
    "AXAMSMSMMMSAXMMMMAMMMMSAMXMMXSAXXAMXSAXMXXSMMMMMXMSSMXAAAXXXMAAAAAMAMAMAMM"
    "AMMAMXSMMMMAXMASASXXAXXMXSSXMAMMMAMASMMSSMXSXMAMMXAAXMAXMXMXSXMMMS",
    "SSSMXAXXXASMSMAXXAAAAAXAXAMXAMASMSMMXMSMXAMXMAMAAAMAMSMSMSSMMSSMMMMAMSSMSS"
    "SSSSMSMXSAMSMXMSAMXSMSSXAAAXMASXSAMASXMMAXASAMMMAMMSMMSMSXMAMXMAAA",
    "MAAXMAMSMMSAAMAMXMMSMXSSMASAMMMMMMASMXAAMSMMMASMSMSAMXXAAMMXAXAAXXMAXXAAMA"
    "AXMASXAMSAMAAXXMMMXAAAXMSSSMXSSMSAMMSAMXAMXMAMXXMAAAAMAASXMASASMSM",
    "MSMMMSMSAAMMMSMSASMMXXAXSASAMXMXMSAMAMMSMMASXXSXAAMAMXMMSMAMXSSMMSSXSSMMMM"
    "SMSXMMXXSAMXSMMSASXSMMSMXAAAXAXASMMASMMMSMXSSMSSSSSSMMMMMASMSASAXX",
    "XMAMSAAXMMMAMAMXMXAAMMMMMMSAMXXAXMAXMSAAASAMXMMMMMMSXSAXAMASXAASAAXMAXXXXA"
    "MXSMXMMMMAMSXMASMSAAAXAMMMMSMMMXMAMAXAXXXAAAXAAAAMAMAXSSSMMXMAMXMA",
    "XSAMXMSMXMSMSASXSMMMMAAAXMSAMXSSSMSMXMASXMAXSAAAMAAXAMXSXSAMMMMMMXSASMSMMM"
    "SASMAXAAMAMAXMXSAMXMMSMSMSAXAXSXMXMSSSMMAMMXMMMSMMAMXMAMXAXXMSMSMS",
    "MMMMXSAXAAAASAMXSAMMXSMSMMSAMMXAMAAXXXXMASXSXMASMSSMXMAMXMAMAAAAXAXXAAAXAX"
    "MXMSAMXSSSSXMXMMXMASXAXMXMMSMMMXMAMXAAAAXXMXSXMXXMASXMXMSMMXSAAAAA",
    "XAAXXMAMMSMXMSXASAMMXMAAAXSAMXMMMSAMXXXMXXXSXSAMXMAMSMSSMSAXSMSSMMSSMSMSSX"
    "MAXMMSXAAAAMAMSAMXAMXMAXAMXAMAXSSMSMSMMMSMMMAXMAMSASXSAMAXAXSMXMSM",
    "SSSSSMSMXAXSAMMMSAMXAMMXSMSXMASXMXMSSMMSASMSXMASMSXMXAMAMMMMMAMAXMAXXAASMA"
    "MMSAASMMMMMAXAMASMSSSXSXMAMXSMSAAXSAXXXXXMASMSAAXMASASASMSSMMSAAAX",
    "XAMAAAXASAXMAXXXSXMMMSAAXXMASASMMMMAAMXAASASAMXMASMMMMMXMASAMMSAMMAMSMSMMA"
    "MMMMMXAXXAXMSXSAMXAAAAAMXSXMMXAMXXSAMSMMXSXSXMAMSMAMXMASAAMAASXSSM",
    "MAMSMMMAASXMMMMXMMXSSMMXSASXMAMMXXMSSMXMSMMMMXSAMXAMAMSMSASXSXMAMMMMAMAMSS"
    "SMMSASXMXMSXAAMMSMMMMMMSAXSXSXXXMMMMMXAAXMMMMMAXMMMSXXXMMMMMMSXMAM",
    "SXMXSMMSMAXMAXSAMXAXAASMSAMXMMMSMSMMXMMMAMXMAMMAXMMMASAAMMSXMASXMXMXASMXAA"
    "AAAXMMSAASMXMXMASXSAASXMASMMSAMXXAAXXMXMMAAAASXMXAXMASMXAXXSAMASAM",
    "AASAXMAMXAASMASASMMSSMMXMMMXXMAXAMMAXMAXAMAXMASAMXMSXSMSMAXASAMXMASXMMMMMS"
    "MMXMXAMSMXAAXAMXMAXMMMAMMMXASAMSSSSSMSMMASMMMSMMSMXMAAMMMAAMASAMAS",
    "SSMMSMASMMXAXXSAMAAAMASAMASAMXMMMMMSSSSSSSSMSXSASAMSAMXAMXSXMASAMAXMAASAXX"
    "AASXMMMMXMSMSSSSMSMSMXAMAAMMSAMXAXAMAAAMMMXSMXAXXXXMSMMSSSMSAMXSXM",
    "XMAMXMASXMAMMXMASMMMSASASAMAAAMMSAMAAXAXMAMASMMASMMMAMMAMAMMSXSAMMSMXMSSXS"
    "MMMAAXAXAAAXMMAMAAAAAXSSMSSXSMMMSMMMSSSMAXAAASMMSMSMAMXAAAXMASXMAS",
    "MMAMAMAXAMSXSXXAXAMAMMSMMASMSMAAMAMMMMSMMAMMMAMMMMASAMSSMMSAMAMAMSAXXAXMMS"
    "AMSSMMMSMSMSMMAMSMSSMXMAXAMXMASAXAAXMAMMXMXMAMXAAAXSMMMMSMMSAXAXAS",
    "SSMSXSXSSMAAAXMMSAMXSASASXMAAMXMSSMSAAAAMXSXSSMAASMXAMXMASMXSASAMMASMAMXAS"
    "AMAAMXXXMAMAMMXMXXAMXASMMMSAMAMMSSMSMSMMMAASMSMSMSMSXSAXAXXMASMMAS",
    "XAAAXXAAMAMMMMXXAXXMMASMMAXSXSXAAAASMMMSMSMXMXSSMMMSSMASXMAXMAMASMAMXMMMMM"
    "AMSSMMXSSMSMXSXSAMXXSASMAASMSMSAXAAMMMAAASMSAAAAMAAXAAMSASXSAAXMAS",
    "SMMSSMSMMXSSXMMSMMXAMXMXSSMMAMMXMMMMSXAXMAXAXXMMMSMAAXASAMMMMSMMSMSMAMMXSX"
    "MXXXXMAMAMXXAAMXMAXAXXSXMXSAAAMMSMXMAMSMMMAMMMSMSMSMSMMMAMAMSSXMAS",
    "XMAMAXMASAAAAMXAAAXSSSMXSXXMAMMMXMSAXMMMSASMSMXAAAMXSMXSAMXAAXAXXAXSASMASA"
    "MXMAMMASMMAMMSMAMSMSMXMASAMMMSMXXAXMMXAMAMXMXMAXAMXAMXMXAMXMMMMMAS",
    "MMSSMMXMMMSSMMSMMMSMAMMMMAMSMMAXSAMXSASAXAXXAXMMMMMAMXAXAMSMMSMMMMMSXSMASA"
    "MAMAMMAMAMXMMAXAXAAAAXMAMASXAXMXMMMSXAXSMSASASXSMSMXMASXXSXXXAXMXS",
    "MMMAXMAXMAMXMXAXAMMMMAAAMAMAMXMSMXXXMXASMMMXAMXSASAMXMMSMMXXMAXAASMMMSMMXA"
    "XSSMSMMSMMSXSASXMMMMMAAMSMMMMSMXAAAXMMXAASXSASAXXSAMXAMXSMMMSMXAMX",
    "SAXXMSSSMMSASXXMMXXXXXXXXASASAMMMSXMXXMMSMAMMAXMASAXXSMSAAMXAMMSMSAAAXMASM"
    "MAAAXXAAMMSAMXXMASXMSSSMAXAXMAMSSMMSAMMMXSAMMMMSMXAMSAMSAXAAAMMSMM",
    "SAMSAMAAAASXMAMMSMMSSSXSMMMAXXSAAXAMMMXMAMSASMMMMMXAAMAMMASXAXAMMXMMMXXMAS"
    "MSMMMSSMSAMSMXMMAMAAAAAAXMMMSAXAMXAXAXMXAMAMXAAAAMAMSAMAMMSMMMAAAX",
    "MAMXAMSMMMSASXMAAAXAAXMSASMSMAMMSSSMAAAMXXXMSAMXSAMXXMAMSAMXMMMSASXSSMSMMX"
    "MMAMAMMXMASAMAXMASMMMSMMSMSAXMSMMMSMXMMMXMMMSMSSSMXXMAMMXMXASMSSSM",
    "MAMXAMXAXXSAMAMXSSMMSMASAMAAAXMXMAMXSSMSSSMXSXMSMAMMMSXXMMSAMXMMASAAMMSAXM"
    "SSSMAXXAMXSASAXXAMAMXMAASXMASXAAXSXAMMMMSMSASAMXXXXXMAMXAXMAMAXAAA",
    "SASXAXSXMXMASXMAMMAMAAMMXMXMSAMXMAMAMAMAAAMASASXSAAAAAXSAAMMSAAMAMMMMAMAMX"
    "AAASXSSXSMSMMMSMAMXMAXMMSAMMAMSSMSMSMAAMAAMASXSXMAMSMMXSMSMSMXMSMM",
    "SAMMSMMAAXSAMMSXXMAMMSMMAXASXXSASAMMSAMMSMMASMMAMSMMXSXMMMAAXMMMSSSMMSSMSM"
    "MMMMMAAMAAXXAASXSMSSXSAMSXMXMAXMMMAAMXMSMSMXMAMMMAAAASMSXSAAAAXXXS",
    "SASAMASXSXMAMAAASMMXAAASMXXMAASXSXSASAMXXXMASAMAMMXSMMMXSMMMXSXXMAXMAXAAXM"
    "SMSAAMMAMSMSMMSAXAMAXAAMMSMXXXMSAMSMSMXXMAMMMAMXMMSSSMAMAMSMSMMSAX",
    "SAMASAMAMMSSMMMSMAAMSSMAMSMMMMXMSAMXSASMSAMAXAXSMSASAAXAXAXMAXMMMAMMSMMMMX"
    "MASXXXXXXAAAMMMXMSMMMSSMAAXSASASMMAMAXMAMXMSSSMXMAAXAMAMMMAMAAXMAM",
    "MAMMMMMSMAAMAASAMMMMAAXMAAAXAMXSMXMASXMAXXMAXSMXAMAXSSMSSMMMMXAAMMSAMAMMMM"
    "MAMMSMMMSMSMSXAMXXAMAAAMSSXSAMASXSMSAXMAMSMAAAASMMSSSSSMXMASXMAMMA",
    "SMMAAXXAAMSXSMSASMSSSXMXSXSMSSXMASMASAMSMSMSAAMMSMSMMMAXMASAMSSMSMMASMMAMA"
    "MASXAAAAXAMAMXMSASMMMSAMXMAMXMXMAMAMAMMAMAMMSMMMAAAAXAAXSSMSAMASAM",
    "XAXMMMMXXMXAXMMMMMAAMAMXMAAXXMASXMMSSXMAAAAAMMXAAAMAAMMMSAMAXAMMMMMXMXSAXA"
    "XMMXXSMXSAMXSAAMAAXXXMASMMXMMMMMAMAMMASMSMSAXAMSMMMSMMMMMAMSAMASAM",
    "SSMSSSSSSXXMXAAXAMMSMMXAMXMXXMAMAXMASAXMSMSMXXMSMSSSMSAAMMSXMASAXAMMXASMSM"
    "SAAMXMXMMAXXMMXMXMMSSMASAMMAMXASMSXSMMMXAXMASXMASMXXAAMAMAMXMMASAM",
    "AAAXAXAAMAMXMMMSSMMAMMMXMAXAMMMMMMMAXXMXAMXXXMAXAMAAASXSXMAXSXMMSMSAMXSXAA"
    "SMMMASASMXMXMASAMXAAAMXSAMSSMMXSAMASXXASAMSXSAMXSMMMSASXMAXAXMAXXM",
    "MMMMMMMMSASAXAMXXAXXSAMMSSSMAAAASMSMSSXMASMMMAAMAXXMXMAXAXAMXMMMSXAMAMXMMM"
    "XMAMXSAMXMMAMASXSMMXSMAMAMAMAMASAMXMAMXAMXMASMMASASAMXAAASMSSSSMSS",
    "MSMSAXXXSASASXSMSSMAXASAMMAMSMSMSAAAAAASASMMXMASMMMXMXAMXSXMASAAXXMXSAAAXX"
    "ASXXAMAMAAXAMAMAMXXAXMMSSMXSAMXSAMXXSMAAXAMAMXMASAXXXMMMMXAAMAAAAA",
    "XAAXASXMMAMAMAAMAMASXMMXXXAMXAXAMMMMMSXMAXASAMAAAXSMMMSSXMASXSMXSAMAMSSSSS"
    "MMSMXSXSXMSXSXMSXMMMSAXXAMASASAMAXAAMSXMXMMSAMXAMMMSXXAAAMMMMSMMMS",
    "MMMMAMAMMSMSMSSMXSAMXSMSMSMSMMMMMSMMXXAXAMSMSMSSSMSASAMAMSAMXXAAMAMMXAXXAA"
    "MAMMMMAAMASAMXXMASAXXXMSMMASMMASMMMXAAXAMSAMASMSSXAXMAXMSSMXMXXAMX",
    "XAASASXMAXMXXXMAMMMSXMAAAAMAXAAAAAAMSSMMMMXAMXAMXASXMASAXMXSSMMSSMMSMMXXSM"
    "MAMAAMSMMASAMSASAMMMXAXXXMASASAMXXXMMXSMMAASAMAAXMSXMSAAMMMAMMMSSM",
    "MSXSASAMXSMSSMMAMMASMMMMAMMAMXSMSSSMAXMAXAMAMMMSMXMMSAMXSSMMAXAMAMAAASMAMX"
    "SXSSSXMAMXXAMSAMASASXXMAXSAMXMAMXMXMMAMAASMMMMMMXMAMAMMMXAMXSAAXAX",
    "XMMMAMXMAAXMASXSSMAMAAAXSMMSSMMMMMAMAXMXMMSAMMMXXAAXMXSMXMASAMXMAMXSAAXAMM"
    "SXAAXAXXMAXSMMAMAMASAAMSMMMSASMMSSSMMASXMMXXXXAMXMSAMXXSSSMMMMMXAM",
    "MSAMXMAMSMMXAMXMAMXSSMMMXAMAAAMXXSAMSMSAAXSASXMAXMSMMMMXAMXMMSSMASAMMMMASA"
    "SMMMMSMAMMMXASAMXSXMMMMAAAASXSAAAAAXSASMSMMMSSMSXAXSXMXAAAXMMAXMXM",
    "ASAMSMXXAASMSSMSAMXXMASMXAMSSMMAMAMXXASMSMSAMXMSXMAAXMAXMXMAXAXXMMXSAXSAMX"
    "SAMAAAXAMXASAMXMAXAXXSXSMMXSXSMMMSMMMXSAAAAAXAAMMMMMMMMMSMMSMASMSM",
    "AMAMMAMSSSMAMAASMMMMXMASMSMXMAMSSMMAMXMXMAXMXMAXAMSXMMSSMASXMXSAXAXXXXMXXA"
    "SAMMSSSMXXAMAXAMXMMMMSAXXSAMMXXAMMMMMMMXSSMSSMMMAAAAAAXXAXAAMMSAAA",
    "MMMMSAMXMXMAMXXXMASXASAMXXMMXSMMAXMXSASAMMMMXMAMAMMXMAXAMASAMASMMSSMSSSSMA"
    "SXMAXMAMSMSSMXMSMMSAMMAMAMAMAMSAMAAAAAMXMAXMAMXSSSMSSMXSASMMSAMXMM",
    "SASMSASXSAXXSXMASXSXMMXXXAXSAMASMMXAXAMMXXAXXMSSSMXAXASMMMMAMASXAMAASAASMX"
    "MAMXSMAMXAAXMASAMAXASMXMMSMMSXMASMSSSSXSXSMMMMMMAXAXAMAMXAAMMMSMMM",
    "SMSAMASASMSMMMSAMXMASMSMMMAMASXMMAMSMSMSMXSSXSAAMASXMAAXAMSSMASMMSMMMMMMMM"
    "MXMASMSSMSMMSXXAMASXMXAXXXASMAMAMMAMXMASAMXXAAMAAAMSAMXSMXSMAXAAAX",
    "XXMAMXMAMSAAAAMASASMMAAAASXSXMMAMAXXAAAAAAXAMAMXMXXMASMSSMAMMMXAMMXXAMXAAA"
    "SAMXSAAAAMAAAMSXMASAASMXXSMMMAMASMMMXMAMAMMXSSMMXSXAXSAXXAMMSSMSMS",
    "MSSMMSMMMXXXMSSMSASAMSMXMXAMXXAXSMSMSMSMSMXASXXAXMAXMAXXAMXSXASMMMMMMXSSSS"
    "SSSXMMMXXSMMSAAAMXMMMMXSMXMASASXSASAXMMSSMAMMMMSAMXSSXXXMASAXMAMAS",
    "AAAMAMASMSSMMAMAMAMXMXMXSMSMSMMMXMAAXXXAAXSXMMSXSXXMSMMSXMMXMXXMASAASMAAMA"
    "MAMMMXSXMAXMAMSSMSXAXSAAAXMASASASAMMXAAAMMXSXAAMASAMAMMXMSMXMMSMAM",
    "SMMMXSMMMAAAXAMMMMMMMAMAXAXAXAMSASMSMSSSMMXAAXSMMMSMAAXMASASMSMSAMSSMAMAMA"
    "MAMSMAMXAXXXMAXAAMXAMMXMMXMMMXMXMXMASMMMSAASXMMSSMAMMAXAXXXAMXXXXA",
    "AMAMXAMAMSSMMXMAAAAAXAMMMSMMMSMSAMAXAAXAXXSSMMMAAAAXMSASAMMAAAMMSMXXMSXASA"
    "SAMAMASASMMMXSSMMASXXMMSMXMXMXAMXXXXAXSAMMXXAXAXXSXMASXMSMSMMMMMMA",
    "MSASXMSAMMAXAMSSSSSSSXSXAAAMXXXMAMAMMSMXXXAAMSSSMSSSSXMMMSSMMMSAMXAXMASXSA"
    "MMSXSAXXXAMXAAXAMAMAAXAAAAMASMASXSMMSXMASMSSSMMSXMXSMAAAAAAMAAAAAS",
    "XSASXXSXMSAMXXAMAAAAMMSMMSSMMMMSAMXXAAAASMSAMXAXMXMXMAXMMAAXXXMMMMMMSAMXMM"
    "MAAAMMSMSSMMSMSXMASXMMSSSXSAXSAMXMAMMMSAMXAAMAXSAMASXAMSMSMSSXSSSM",
    "XMASMXMAMMASXMASMMMXMAXAXAAAAXAXXXSXSMSMXAAMXMMMSAMASXMSMSSSSSMXAMXAXAXXAA"
    "MSMXMAXMAMAXAASMSXSAMAXMAMMXXMXSXXAMAAMASMMMMSMXAMASAMXAAMMAMAAMAM",
    "XMAXMAMSMSXMASXMXXAAMMSMMMSSMASMAMSMXXMAMMMSSXSASASAMAAAAAAAAAAASMMMSMSMSM"
    "XMXXAMXMSSSMMSMAMMMAMSMMSMSMMMMMMASMMXMMMMXSXXMSXMAXXSSMXMMASMMMAM",
    "AMASXMXAAAAXMAMSAMXMXXAXAMAAMAXXMMSAMSMMSAAXMAMASMMASMSMMMMMMMMMMAAAXXAAAX"
    "XMASMXMMMAMXXAMAMMSMMAMSAAAAAAAAAMXASMSMAAAMASAAAMMXAMXMASMMSAXMAS",
    "XMASASXMSMSSSMXSXMASMSMSSMXXMXSAMAXMAMXAMMSSMXMAMASXMXXXXXXMAASXSSMMSSMSMS"
    "SMAXMAMAMAMMSMSXMXASXXSXMSMSMSSSSXSAMAASMMXSAMXMMXXAMXXMASAMMMXSAM",
    "XMMSMMAAAXXAAMXMASMSAAXAXXAMSMSXMAXSSMMMSAXAMMMSMMMMSMMMSMMSSSSMAAAAMAAMAM"
    "MMSSXSSXSXSAAMAMXMASXXMAMMAXAAAMXMAMMXMXXAXMMMMXMAMSXMSMAXASAMXMSS",
    "SMXSXSMMMMMSMMASXMAMMMSSMMXSAAXMASMMAAAAMASAMMAMAXXMAAAAXAAAMXMAXSMSSMMMAM"
    "AMXAAXAMXMMMMMSASMAMASXSMMAMMMXMMMMMSMXMMMSMAAXAMAMAAXXMAMXXAXXAAS",
    "SXAMMXAASXAXXSAXAMXMAMAXAMXXMXMMSMASMMMSSXSAXMASMMSXMMMXSMMSSSSSMMMAXMAMAS"
    "ASMMMMAMMXMASXMAMXAMXMXAMMSSXMXMASAAAAAAAMXXSMSMSXSSSMMMMMSSSMMXMS",
    "MMMMAMSMMMXSAMXSMMMXXMASXMMMSMAXMXAMXXMAMAMXMMAXAAMMSSSXXASMXAAMAXSMXXMXMS"
    "AXAXXXMSMXSASAMAMSXSXAXASAAMAAXXAMMSMSMSSMAMMASMSXAAAMSAAAXAMXAAAX",
    "SXMASMXASAAMAMMMAAXMSXMAXAAAAXMMSMSXSXMASMSXSMSSMMXAAAMAMSMMMMMMMMMXSASAMM"
    "MMSSMAMAAXMXXASXMMAXMAMXMMSXSMMMMSXMAXXMAMXSMAMASMMMMMSMSSMAMXSMMM",
    "AXSAXASAXMXMSMASMXMAXAXAXXMSSXSAXAAASMMMSXMMMAXMASMMMMMSMXAMXMXSAMSASAXMMA"
    "MXMAXSMMSMMAXMMMAMAMMSSXSSXXMAXAAMASAMASAMXMMXMAMAXXXMXAAXXXSAXAAA",
    "MMMAMXMXMMXXAMASXAASXMMMSMMXMASXMMMXMAAXMAXAMAMMAMXXAMXAASAMAMMSASMAMMMSSM"
    "SSSMMXASMMXMASAMAMMSAAAAXASXMSMSMSAMXSAMAAMSSMMXSMMMMMMMMSMXMASMMS",
    "XXMAMASXSAASXMASMXXMAMAAAMMSMMMXSXMXSSMSASXSSSMSASMMSXSMAMMSAXXMXMMXMAAAAA"
    "AAAXASMMAXMXAXASXXAMMSMSMMMXAAAAAMXMAMAMAMXAAXSAMXXAAXXSMXMAMXMAMM",
    "SMSMSMSAMXMSAMXSAMMSMXXMXSAAAAXMASXAXAXMXXXXAAXAASAAMAMXMAMSASAMSXXSSMSSMM"
    "MSMMMSXMAMMMMMXAXMASAXXMAAAMSMMMSMSMXSSMMXMSSMMASMMSXSAMXMSXMASAMS",
    "AXAMXAMAMXAMAMXMMSAAMAMSMMMSSMMAMXMXSSMSAMMMSMSMMMMAMAMSMMXSAAMAAASAMXAMAM"
    "XAMXASAMAAMAMXMAAMXMASMSSMMXMAXAXAXXMAMAMXMAXASAMXAAXMAMAAAXMXXXSA",
    "MXMSMMMAMXMXSMSAAMXMMASAAMAXAMXMXAAXMAAMXXAAAXAXXAXAMAMAAMASAMMXXXAXXMXMMM"
    "MXAMXMAMASXXSXMXMASMMSAAXXMASMMSMSMSAXMSMMMASMMASMSSMXAMXMASMAXXXM",
    "XAXAMXXAXAXXXAMMMSSMXXSXSSXSAMSSSMSXSMMMXXXSAAMMSASMSSSMSMAXAXMSSSMXMSSMAA"
    "SMSMSSMMMMAXSXSAXXAAAMAMSAMXMXAMXXASMSMXAAXXSAMXMXAAXSSSMXAAMMSMAA",
    "SMSASMSMSASMMXMAMSXSAAMAMAAMAMAMAAXMASMSSXMAMAXAXAAAAMMMXMMXSMSAAAXAMAMSMM"
    "XAAAAASMMMMMXASMSMSMMMXAMXMAMXSXMMXMASAMSMSMXMMSSMMMMXMAMMSXXAAMMM",
    "AASAMAAXXXMMAXSSXMASMSMSMSMSAMMSMMMAMAMAMMMSSSSMSAMMMSMMMASAAXMMXMXXMAXSMS"
    "MSMMMSMSAAMMMMMAXXAMASXXXAMASXMAXSXMSMMMXAMXXAAAAMASXMSAMXMMMSSMSX",
    "MAMAMMMSMAMXMMXMAMAMXAAXMAXMAMXXXAAAMAMXMAAMAAAAXAXMAMAASAMSSMSXSMSMSMSMAX"
    "AXSSXMASXMAAMAMXMMASASAMSMSASASMMMAMXAXAMAMASMMSAMXSAAMMMAXMAMAASX",
    "XASAMXAXXXMAMXASXMSSXMSMMMMXSMMSSMSXSMSMXMXSMSMMSMMMASMMMAMXXAXAXAAAAMAMXM"
    "XMASAMAMMMSASASAMMAMXSAMXMAXSMMMAMMMSMMMSAMXSXAXAMXSMMMMSASMSXMXMA",
    "SASXSMXXMXSMSMMMMMAAXSAMXXAAMAMXAAMAXMAXAAMSAMXXAXAMAMAASXMMMMMMMSMSMSSSMA"
    "AMXMXMXMAAAXSASASAMXASAMASXMMXMXAMAAXXAXXAMMXMMSMMMMMMAMAAMAMASMMM",
    "XAMXMXSAMAMAMAAAAMMSMSASMMMMSAMSMMMAMSASMSMSASMSMMMSSSSMMXMAMAAXMMMMAAAMAX"
    "XXSMMMMMMSXMMAMAMXXMASAMXMASAAMMSMMMSMSSSXMMXSAAAASAAXAMMSMXMASAAX",
    "MSMSAASAMMSASXSSXSXMAXAMXAXASAMMASXXAMASXMAMAMAXSAMXAAAMXXSASMMSASXMMMSMSM"
    "SXAAMXAMXMAAMXMAMXMMAMMMASXMSXSAMAMMAMMMMAAXAMSSSMSSMSASXAMAMASMMS",
    "XAAMMXMXMXMAXAAMMSMMMMSMMSMMSAMSAMMMAMXMASXMMMSMSSSMMMMSSXMASAASAMASXAXAAA"
    "ASMMMSMSAXMMMSSXSAMMSSMSXSAMAXMAMAMSMSAAMXMMXXAMAAXAXMXMXSMMMAMAXM",
    "SMXMXMSMMXMSMMMSAXXAAMAAAXAXSXMMXSASXMMSAMASXAAAMXMAMAXAXAMSMMMMAMXMMMSSMS"
    "MXMAMAMMMSMAAXMASASAMAAMMSXMASMXXAMAMSMXSASAXXMSXMMSMSXMAXAMMMSMMM",
    "AMASAMAMXMAMXAAMASMSSSSSMMAMMMMMMMXSAAAMASAMMXMXMAXAMXMMSXMASXXXAMXSXXAMXX"
    "AASMMASAMSMMSSMAMMMMSSMSXSMSAMAASXMMMXAASAMSMMXMXMAAAAAMASMMAMAAAM",
    "MMSSXSASXMSMSXSMAMMMAAAAXMMAMXAAAMASMMMSAMASAXSASXSMSMAXMASASMSSSMXSMMSSSM"
    "SXMXXXMAXXXXMMMSSXAXMASAMMASMMSMSAAXMMSMMXMAMMAMMMSSSSSMXMMSXSXSSS",
    "XSAMXMXSXAAASXMMMSMSSMSMMXSAMSSXSMASASAMXSAMXAXMMXSAAMAMSAMXXAAMAMAXXAAMAA"
    "MXMSMSMSSMMMSAAAXMASMXMMAMAMAXMAXMMMMMMAXMSSMSAXSAAAXAXXAAMMMMMMMM",
    "MAAMSMMMMSMXMAXXAAAXAAAXAXXAMAMAXMMSAMXSAMXSSMSXSAMSMMSAXXMMXSXSAMSSXSXSMM"
    "MAXAAAAAMAAASMSXXXMXXSMXSMMSMMMSMMXAASMXMASAASASMMSSMMMSSSMAAAAAAM",
    "SSXMAAXMAXXASMMMSMSSMMMXSMSSMAXMMSXMASAMXSMMAXAXMAMMXMXMSMMSAAMSASAMXMMXXM"
    "XXXMSMSMSMMMSXMMSSMSAMAAMAXAAMAAAXMSXMASAMXMMMXMAXAMMXAMMAXSSSSSSS",
    "AASXSSMMMSSMMAAAXXMAMXXXMMAMSMAAMXAMAMASMXASMMXMSSMMXMAXXAAXMMMMMMXMASASMM"
    "MSAAXXMASMMXMAMAAASMAMXSSMSSSMSSSMXMMSSMSAMXMXMMXMSSMSMMSAMMAMAAXX",
    "MMMXAMASMMAMSSMSMXSAMXXXAMAXAXMMSXSMASAXMAXAMSSMMMASXSMSSMMSMSMSXSASASMMAA"
    "AXXMAXSASAXAMAMMMSAMAMXMAXAAMMXAMMMAAMAAXXAASAXXXAXAXXAAMXSMMMXMAM",
    "MSMMXXAMMXAMMMAAAASAMMXSMSXSAXSASAXSMMMSXXSXMASAASMMASAAXMAAXAAAASAMXSMSMM"
    "XSAMXMMAMXXMMSXXXMMMMXXMAMMXMXMXMAXMMSMMMSSXSASMMMSMMMMMSASAMMAMXM",
    "MAAMSMSSXSASAMXMMMSAMSMMAAXMASMAMMMXSAXMAMMXMASMMSAMXMMMMMSSSMSMMMXXMMXAAA"
    "ASMMMMMMMSXMAXMAXXXASXSAXSMXAXSXSASXMSAMAMAAMMMAAAAAAAAMMMSAMSMMAM",
    "SMSMAAAAASXMASAXXAMAXMAMMMMXXAMXMSMAMMXAMXAMMXMAXSMMSMAMSMAMAXXXXAXSXMSSSM"
    "XMMAXMAMAXAMASAMMXSXSASAMAXAMXMXMAMAAXSMASMAMASMMMSMMXMXAAXMMAMSAS",
    "MAAXMMMSMMXSMSASMSMMMSSMSSMSXSAMXAMASMSMSXSAAMMSMMMAXSASAMASAMAMMSMMAMAAXM"
    "MMSMXSASMSSMASMMMXXXMMMMSXSXMAMMXMSMMMMMMXXMAMMAMAMAAASMXMXAXAXSAM",
    "MSMSXAXXAMXSAMXXXXASXXXAMAASXMAXSASASAAAXAAXAAAAAXMSMMXSASXMMMSXAAASAMMSMA"
    "AXAMMSAMMAAMASAASXXMAXAXSXMASMSMAMAXSXMASXMASMXSMAMMMMSAAMSSMSMMAM",
    "XAXMXMSSMMMMMMMMMSXMAMMXMMMMASAMMASMMXMMMMMMSMSSSMMXAMASMMMXSAXMXMMAMMAMXS"
    "MSASAMSSMMMMXSXMXXMASXMSMMSXAAAMSSXSAXSAMAMSMSAMMMSMMXXMMMAAXXASAM",
    "XMSMAMAMXAAAAAAAMMMSAMAXSAMXMMMMSAMXAAMSSXSXXAAMAAASAMXSAXXAMASMMSXMSSSMXM"
    "ASAMXSASASMMXMMSSMSAMXMAMAXMMSMMMAMMMMMASXMAAMXXAAAASMMMSMSXMMAMXM",
    "MSAMAXASXSMSSSSXXAASXXXSAMXSAMXAMASMSMSAMXXMSMMXSMMMAMASXMMXMAMAXMAXAAAXMM"
    "MMAMXMASXMAMXMAMAXMXMAXAMMMAXAMAMAMMXMSAMASMSMSSMMSXMAMAAMXASMSSMM",
    "XMAXMSMSAMXXAMXMMSXMXAMXAMAMAMMMXAMXMMMMSMSMXAAXXAMSSMMMAXXAMXSMMMMMMSMMXA"
    "AXAMXAMXMSAMAMSSMMMMSXSASXSSSMXAXASXAAAXSXMAAAAXMXXXSXMSSSXMMAAAAM",
    "MXSXAAAXMXMSAMAMMXAMSSSMMMXXAMXSMSSMXAAXAAAMMMMXSAMAMASXMMSMSAMXSAAAXAXMSS"
    "SSXSXXMAXMAXAXMAXMAAAMXAAMXAAASXSMSMSSXXMAMXMMMSMXMASXAMAMAXMMMSSM",
    "SAMMSMSMMAMXAMXMAMAMAMAAMSXSXSAAAAAASXSSSSXMAASXSMMXSAMASXMAMXSAMMXMMMXMAA"
    "AAASMASXSSMXSMSAMXMSSMMMAAMSMMMAAAXAAMMMSSMSXSMAMXMAMMAMASMMSAAMAA",
    "MASAAAAMMASXSMSMXSAMASXMMSAAASAMXMMMAAMAAAASXMMMSAMAMMSMMAMSMAMMSSMMMXSAMM"
    "MMXMAXAAAMAAXXMXSXAAAXMAAMMAMAXSMMMSMMAAAXAAAMMAMXMASAXMASXAMMSSXM",
    "MAMXMSMXXASAXAAMMMASASAXAMAMMMXXMMXMMMMSMMMMSAAASAMXMAAAMAMXMAXMAAAAAAAMAX"
    "XXAMSMMSMMMMSAMASMMSXMMSMXMASMMMXXAAMXSSMMSMAMSMSMSASMXMAMMMSMAMMM",
    "SSSSXMXMASMXMSMSASAMASMMAMXMASMAMXAMXXAAXXXAXSMMSXMASXSSSSXXMAXMXMMMMMSXAX"
    "XSXSAAXAAAXMMAMAXAXXMMMAMASAMMAXSMSXSAAAXAMMXMAMAAMAXMXMASXMAMAMAX",
    "SAAAAMSAMXAXMXXSXMMSMMMSMSMMASASMSSSMMMSSXMAMMSMXMXMAXAXAMXSMMSMSASXAXAMXM"
    "XAXSXXMSSMSSSMMSSSMMAXSASAMASXSMMXMAMMSMMXMSASASMSMASXMSASMSSSSSSS",
    "MMMMMMXMAXMXAAMMMMAAXAAAASASAMXAAXAAXASAMXMMMMASXASMSMSMSMAMAMAASAMXXAMXAA"
    "XMMMXXMAMXAAXSAMXMASMMMXMAMAMXAAXAXMMAAXXAXXASXSAXMASMAMXSAMAAAAAA",
    "MMXMASXSSMSMMMSAAMSMSMMSASAMASMMXMSMMSMASMMSASAMMMXAMAMAMMXSAMMXMAMASXXSXS"
    "MXAASMMAXMXMSMMMAXXMXAXMSSMAXASMMMSXXSASMMSMMMXMXMMAMMAMMSMMMMMMMM",
    "MASAMSAAASMAAAMMSXXASXAXMMXMMAMXSAAMMMXAMAAMMMAXAXMXMAMAMAMSASXXSAMAMSAMXM"
    "ASMMMASAMSAMAAMSSSMMXSAAAMSMMMXSASXMAXMMMAAAASXSXAAAXSASAMXXSASAXX",
    "SASMXMMMMASXMSSMMAMAMXXXAMXSMAMAMMXSASMMMMSXMXSMSSSMSXMAMAMSAMXAXXMASXMASM"
    "XMSASMMMXSASMMMXMAMAAAMMMMAMXMASXMXMAMAAMMSSMSAMMAMXMXAMXSAASASMSA",
    "MASXXMXAXMMXAAAMXAMMMMSSXMASMXMASMMMMSAXSAMXSAAMAMAAXMSMSMXMMMMMAMMMSMMASX"
    "AXSMMAAXAXAMXSAXSAMMMSXMMSMSXMAMASXXXXMMSAAAAMMMMASMSMSMSMXXMAMAXA",
    "MMMMMMMMMXSMMSSMXXXAXAAAAMAXMAMXMAAAASXMMASAMSMMASMMMMAMAMAAAAAAAAAAMAMASM"
    "MMMXSSMMMSMSMAAMMMSMAMASXAXAAMXSAMMSMSMAMMSMMMAASXMASAMXXMMMMMMMMM",
    "SMAXAAAXXAXAMAXASXSMSSMMXMASXXSAMSXMMMXXMAMAMAMSMMXAAMASXSSXSMSXMMMMSXMAMX"
    "MAXAAMAXXAAAMMSMXAAMMSAMXMMSXMXMMAMXAAMXMAMXXMSASAMSMMMSSMAMASAMAS",
    "MXMXSXSXMXSXMASAMAAAAXXXAXAXAAXMMAXSAMMMMASMMMMAAMSXXXASAXMAMAMXSASXMAMMMS"
    "XMSSSSSMSMSMSXAXMXSSXMAMASAMMSMXSMSASMSXMXSMSXXAMMMAAMAAAXMSASASAS",
    "SASAMMXASASAAXMAMSMMMSSSXSMMMMMSMSMXAAAXMASAAMSMSAMASMMMMMMXSAMASASMSAMXAS"
    "AMXAAAMAXAXXAXXMMSMXXSXMMMASAAAAMASAMASMSMAAMAMXMASXSMMXSMAMASAMAS",
    "SXMASASAMASAMXSXMMAXSAAXMXMASAXAAXASXSSXMMMXMMXMMAMAMAAAAAMAMAMXMAMAXSXMAS"
    "AMMMMMMSMMMSMSSMSAAXMASXXMAMXMSXMXSAMXMAAXMMMAMASXSXMASXMAMMMMAMSM",
    "XMASMAMAMXMAXASAMSSMMMSMSASXSMSSSMAMAAAMSSSSMXXXSXMAMMSMSXSMSMMMMMMSMMXSAS"
    "AMAAXAAXAMASXAAXAMSMXXAMXMASXMAXMASMMXMSMSMMSASXXSXASMXASASXSMMMAM",
    "SAMXMMMMMMSSMASAMAAXSXXXSXXAXMAMAMMMMMMMXAAAXXSAMXSSSMMXMXSXMASXMAAAAXMAAS"
    "AMSXSMMXSMASMSSMXSAAMXMXMMAMXMAAMAMAAXXAXAAASAXXMAXAXMSMSAMXSAASXS",
    "AXSXMAAAAXAXMASMMSAMXAXAMMMSMMSMSMSASMMSMMMMAMMSMXXMAXXASAMAXAMASMMSSMXMAS"
    "XXMAMASAXMXSAAMAXMMSMSMASMMXXMSXMSSSMXSSSMSMMMAMXMMMAAXXMAMASXMMAM",
    "MMMASMSSSMSSMASXXXXMAXMAMAAAAAAAMASASXASAMAMASAMXXASAMSMMASAMXSMMSXAXAMXMS"
    "MSXMSAMXSSSMXMXSAMXMAMMAMAAASXXXXMXAXMAAAAMXXAAMAXAXMSMMSMMASASMAM",
    "XASXMXAMXAMXMSMMMMAMAMSXMMSSMMMSMAMMMMMSASXSMXAMMMMMAMAMMMMMSXAXAMMMMSXXXM"
    "AMAMMMMAXMAMAXMMMASMMMSMSXMMSAMXSMSMMSMSMMSSSSXSXSSXAAMXASMXSAMSSS",
    "SASXXMSMMSMXMAAAXMAMAMMASMXMMSAAMAMXXAXXASAXXSMMASXSXSMSXMAAXMAMXMAAAXMMXM"
    "XMAMAAMMMXAMSMAAXMMAMAAXMASXMAMAMMMXAMXMAMXAAAAXMAXMSMMSMSXAMXMAMM",
    "SAMXAAAAAXMASXSMSSXSXMSAMXSAASMMMAMMMSMMMMMMXAXSAMAMXSXMASXSMSMSASMSMSAMAM"
    "ASMSXMAASMMMAASMSXSAMMMXXASASXMASASMMSAMSSMMMMXMASXMAMMMMXMASAMMSM",
    "XAMMMSSMMMMAMMAAXAASAMMSSMMMMXAXSXSAAAXAAAAXXMXMASMMAMAMMMXAAAAMAAAMXSXSAS"
    "XSXMAXMMMASXMMAMXMSMSMXAMXSAMXSASASAAMAMAAASXXAASMMMAXAAMAMXSXSAMX",
    "SAMXAMAMSSMMSXMAMMMMAMAMMXAXMSSMMSSMSSSSSSSSMXMXAAAMASAMXXSMMMSMSMAMXMASAS"
    "MXAXAASXSMMAMMAXMMSXAAMSMMMXMAMMSMMMMSMMSSMMSSXMXAMSXSSSMAXASAMXSX",
    "MMXMASXMAAAAAAMAMXASMMXSASMSMAXAXMXXXMAMAXAXMASMMSXXAXAXAAAAAXXAXAMXAMAMMM"
    "MSMMSXMASASAMSMMMASMMXMAAXMAMXSASAXXAAAMAMXMXMSXMAXAXMAMXXMASXSAAM",
    "XXXSXMXMSSMMSMSASXXXXXSMMMMMMASXMMMMXMAMXMMMSXSXXMMMSSSMAXXSMSMMMASMMSXSXA"
    "AAAAMAMAMMMAMASMMASXSASMSMSAMAMAMMMMSSSMMXAAAXAXSXMSMSAMXSSMMMMAXA",
    "MSMMAAAXMXAAAASMMMSMXMASAAASAASAASAAMSASMASAMAMXAAMMMAMMMSAAXSAAMXMAMMAMMM"
    "XXMMSAMASXSXMMMMMMXASXSAXXSASXMSMSAXAXAAMSSSSSMXSXXXAMXMXXMASASMSS",
    "AXASMMMMMSMMMXMMSAXMASMSSSSSMXSMSSMXXAAMXAMASAMSSXMAMSMAAMMMMSMMSSSMMSAMAS"
    "AXSXMXXAMXSAMXASXAMMMMMAMAMMXAAAASMSMSMMMAAMAAXASMSMAMMMSASAMXAAAX",
    "MSXMXMXAXAAAXMAMASXMAMXMAXAXAXMMAXXSAMMMMMSASMXAMASXXAMMMSASMXASAAAAASAXAX"
    "MXMAXASXXMXMXMMMXAXMAMMAMAMASMMMXMAAXAXXMMMMSMMMSAAMAMXXAAMMSAMMMM",
    "MXMAASASMSSMXXMMAMMSSMAMXMMSXMAMXSMMAXAMAAMMXXMAMMMSSMSXASXSAMXMASMMMSAMSS"
    "SMSMMMXAASXMSSSMSSSSMMSXSXSMSSMSSMSMSSSMASXAXSMASXMSSSSMMSMXXMXMMM",
    "AXASXMAXXXXMASMMMSAAASMMMAMAXMXMAXXSAMMSMSSMXSSSMSAAMXMMMMXXMSMSXMASAMAXAA"
    "AAAXAXMSMMAMAXAAMAAMMAMASAMXSAMAAMAMXAAXAMMSMAXAXSXXAAXXXAASMMASAM",
    "MAXXSMMMMSMMASXAAMMSXMSAAXMAXMAMSSMMASXAXXAMAAAAMMMMSAMASXMSAXAAAAXMXSMMMS"
    "MMMSASMMMSAMASMMMMMMMAMXMSAMXMMSMMASMSMMMSAAMMMMMMXXMASMAASMASASAS",
    "XMSAMXAAMAXMXSXMMSAMXASXSXMAXSAMXAASAMXAMSAMXMSMMAAMSASASAAXMMSMMAMSAAAXMA"
    "MSAMXAAAASASASAAXXXXSASAAXMSAXMAASASAMAXMMXSSXXMASAXXAMXAMXXXMXSMM",
    "AXMXMSSSSMSMXMASAMXSMMMXAXMAMSASXSMMMSAXMSXXAXMASXSXSMMMSMSMXAMXSXAMSSXMSX"
    "SSXXSSMMMSAMXSXMSAAXSASMSMXSASMSXMASMSSMXMAMMAMXASASXMASAXSAMXXMAS",
};
