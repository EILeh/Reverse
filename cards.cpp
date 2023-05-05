#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if ( top_.get() == nullptr )
    {
        return false;
    }

    // kopioidaan id -arvoon päällimmäisen kortin data -arvo
    id = top_->data;

    // asetetaan päällimmäiseksi kortiksi päällimmäistä korttia seuraava kortti
    top_ = top_->next;

    // smart pointereitten ansiosta muistipaikkaa ei tarvitse itse tyhjentää,
    // huomaa automaattisesti, että poistettavaan korttiin ei ole osoittimia

    return true;
}

void Cards::reverse()
{
    if ( top_.get() == nullptr )
    {
        return;
    }

    // tehdään uusi korttipakka, johon lähdetään kopioimaan kortteja
    // -> uudessa pakassa järjestys käänteinen

    // kopiointi aloitetaan päällimmäisestä kortista, seuraa, että uudessa eli
    // kopioidussa pakassa, nykyisen pakan päällimmäinen kortti on uudessa pa-
    // kassa pohjimmainen kortti ja toisinpäin

    // jos päällimmäisestä kortista seuraava on nullptr, kyseessä olisi viimei-
    // nen kortti
    // smart pointtereiden kanssa varsinainen arvo pitää hakea get() kautta

    Cards new_deck = Cards();
    while ( top_->next.get() != nullptr )
    {
        // lisää uuteen pakkaan kortin ja siirtää ylintä korttia yhden eteenpäin
        new_deck.add(top_->data);
        top_ = top_->next;
    }

    // lisätään vielä pakan viimeinen kortti new_deck muuttujaan
    new_deck.add(top_->data);

    // asetetaan korttipakan päällimmäinen kortti new_deck muuttujan päällimmäi-
    // seksi kortiksi
    top_ = new_deck.top_;

}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
