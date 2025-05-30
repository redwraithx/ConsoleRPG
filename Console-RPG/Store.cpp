#include "Store.h"
#include "Armor.h"
#include "Weapon.h"
#include "Potion.h"

#include "Debug_Mode.h"

#include <iostream>


// Prototypes
void init_armors(std::vector<armor>& armors_container, const std::string& player_class);
void init_weapons(std::vector<weapon>& weapons_container, const std::string& player_class);
potion add_potion(int low, int high, int price);


void store::enter(player& player)
{
	// init weapons
	init_weapons(m_weapon_objects_, player.get_class());
	// init armors
	init_armors(m_armor_objects_, player.get_class());



	////////////////////////////////////////////////////////////////////
	// DEBUG msg
	if (debug_log.enable_debug_messages)
	{
		std::cout << "debug message" << '\n';
		std::cout << "Weapon Bonus low: " << player.get_weapon_bonus(true) << '\n';
		std::cout << "Weapon Bonus high: " << player.get_weapon_bonus(false) << '\n';
		std::cout << '\n';

		std::cout << "original weapon low: " << player.get_original_weapon_value(true) << '\n';
		std::cout << "original weapon high: " << player.get_original_weapon_value(false) << '\n';
		std::cout << '\n';
	}



	// player enters the store
	std::cout << "You enter a blacksmiths shop. You see weapons and armors laid about." << '\n';

	// display the store goods
	bool exit_store = false;

	while (!exit_store)
	{
		
		if (player.get_gold() < 30) // the least expensive item to buy value is a healing potion
		{
			std::cout << "Hi Stranger... it seems you can't afford any of my stuff." << '\n';
			std::cout << "Come back later with more gold." << '\n' << '\n';

			exit_store = true;

			continue;
		}


		// store loop
		std::cout << '\n' << "Welcome to my Store." << '\n';
		std::cout << "--------------------" << '\n';



		std::cout << player.get_name() << " you have " << player.get_gold() << " gold coins." << '\n';
		
		std::cout << '\n' << "1) Weapons list, 2) Armors List, 3) Buy a Potion, 4) leave the Store: ";
		int user_input = 1;
		std::cin >> user_input;



		switch (user_input)
		{
			case 1: // WEAPONS
			{
				bool exit_weapons = false;

				while (!exit_weapons)
				{
					std::cout << '\n';


					// display the weapons for sale
					std::cout << "Weapons List" << '\n';
					std::cout << "------------" << '\n';

					int count = 0;
					for (size_t i = 0; i < m_weapon_objects_.size(); i++)
					{
						std::cout << i << ") " << m_weapon_objects_[i].m_name<< ", price: " << m_weapon_objects_[i].m_sell_value << '\n';

						count++;
					}

					std::cout << count << ") Exit Weapons List" << '\n';
					std::cout << "Enter your selection: ";

					int weapon_selection = 0;
					std::cin >> weapon_selection;

					switch (weapon_selection)
					{
						case 0: // weapon 1
						{
							if (player.get_gold() >= m_weapon_objects_[weapon_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2; // = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Here's your new " << m_weapon_objects_[weapon_selection].m_name << ". Thanks for your purchase." << '\n';

									player.equip_weapon(m_weapon_objects_[weapon_selection]);
									player.buy(m_weapon_objects_[weapon_selection].m_sell_value);

									player.calculate_weapon_damage();


									std::cout << "You equip your new " << m_weapon_objects_[weapon_selection].m_name << '\n';

									exit_weapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << '\n';
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						case 1: // weapon 2
						{
							if (player.get_gold() >= m_weapon_objects_[weapon_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2 = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Here's your new " << m_weapon_objects_[weapon_selection].m_name << ". Thanks for your purchase." << '\n';

									player.equip_weapon(m_weapon_objects_[weapon_selection]);
									player.buy(m_weapon_objects_[weapon_selection].m_sell_value);

									player.calculate_weapon_damage();


									std::cout << "You equip your new " << m_weapon_objects_[weapon_selection].m_name << '\n';

									exit_weapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << '\n';
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						case 2: // weapon 3
						{
							if (player.get_gold() >= m_weapon_objects_[weapon_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2 = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Here's your new " << m_weapon_objects_[weapon_selection].m_name << ". Thanks for your purchase." << '\n';

									player.equip_weapon(m_weapon_objects_[weapon_selection]);
									player.buy(m_weapon_objects_[weapon_selection].m_sell_value);

									player.calculate_weapon_damage();


									std::cout << "You equip your new " << m_weapon_objects_[weapon_selection].m_name <<
										'\n';

									exit_weapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << '\n';
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						case 3: // weapon 4
						{
							if (player.get_gold() >= m_weapon_objects_[weapon_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2; // = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Here's your new " << m_weapon_objects_[weapon_selection].m_name << ". Thanks for your purchase." << '\n';

									player.equip_weapon(m_weapon_objects_[weapon_selection]);
									player.buy(m_weapon_objects_[weapon_selection].m_sell_value);

									player.calculate_weapon_damage();


									std::cout << "You equip your new " << m_weapon_objects_[weapon_selection].m_name << '\n';

									exit_weapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << '\n';
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						case 4: // weapon 5
						{
							if (player.get_gold() >= m_weapon_objects_[weapon_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2; // = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Here's your new " << m_weapon_objects_[weapon_selection].m_name << ". Thanks for your purchase." << '\n';

									player.equip_weapon(m_weapon_objects_[weapon_selection]);
									player.buy(m_weapon_objects_[weapon_selection].m_sell_value);

									player.calculate_weapon_damage();


									std::cout << "You equip your new " << m_weapon_objects_[weapon_selection].m_name << '\n';

									exit_weapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << '\n';
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						case 5: // weapon 6
						{
							if (player.get_gold() >= m_weapon_objects_[weapon_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2; // = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Here's your new " << m_weapon_objects_[weapon_selection].m_name << ". Thanks for your purchase." << '\n';

									player.equip_weapon(m_weapon_objects_[weapon_selection]);
									player.buy(m_weapon_objects_[weapon_selection].m_sell_value);

									player.calculate_weapon_damage();


									std::cout << "You equip your new " << m_weapon_objects_[weapon_selection].m_name  << '\n';

									exit_weapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << '\n';
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						default: // exit weapons list
						{
							exit_weapons = true;

							break;
						}
					}

				}

				break;
			}
			case 2:  // ARMOR
			{
				bool exit_armor = false;

				while (!exit_armor)
				{
					std::cout << '\n';


					// display the armor for sale
					std::cout << "Armor List" << '\n';
					std::cout << "------------" << '\n';

					int count = 0;
					for (size_t i = 0; i < m_armor_objects_.size(); i++)
					{
						std::cout << i << ") " << m_armor_objects_[i].m_name << ", price: " << m_armor_objects_[i].m_sell_value << '\n';

						count++;
					}

					std::cout << count << ") Exit Armor List" << '\n';
					std::cout << "Enter your selection: ";

					int armor_selection = 0;
					std::cin >> armor_selection;

					switch (armor_selection)
					{
						case 0: // armor 1
						{
							if (player.get_gold() >= m_armor_objects_[armor_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2; // = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
									case 'y':
									case 'Y':
									{
										std::cout << "Here's your new " << m_armor_objects_[armor_selection].m_name << ". Thanks for your purchase." << '\n';

										player.equip_armor(m_armor_objects_[armor_selection]);
										player.buy(m_armor_objects_[armor_selection].m_sell_value);

										player.calculate_armor();


										std::cout << "You equip your new " << m_armor_objects_[armor_selection].m_name << '\n';

										exit_armor = true;

										break;
									}
									default:
									{
										std::cout << "No worries, maybe next time." << '\n';
										break;
									}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						case 1: // armor 2
						{
							if (player.get_gold() >= m_armor_objects_[armor_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2; // = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
									case 'y':
									case 'Y':
									{
										std::cout << "Here's your new " << m_armor_objects_[armor_selection].m_name << ". Thanks for your purchase." << '\n';

										player.equip_armor(m_armor_objects_[armor_selection]);
										player.buy(m_armor_objects_[armor_selection].m_sell_value);

										player.calculate_armor();


										std::cout << "You equip your new " << m_armor_objects_[armor_selection].m_name << '\n';

										exit_armor = true;

										break;
									}
									default:
									{
										std::cout << "No worries, maybe next time." << '\n';
										break;
									}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						case 2: // armor 3
						{
							if (player.get_gold() >= m_armor_objects_[armor_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2; // = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
									case 'y':
									case 'Y':
									{
										std::cout << "Here's your new " << m_armor_objects_[armor_selection].m_name << ". Thanks for your purchase." << '\n';

										player.equip_armor(m_armor_objects_[armor_selection]);
										player.buy(m_armor_objects_[armor_selection].m_sell_value);

										player.calculate_armor();


										std::cout << "You equip your new " << m_armor_objects_[armor_selection].m_name << '\n';

										exit_armor = true;

										break;
									}
									default:
									{
										std::cout << "No worries, maybe next time." << '\n';
										break;
									}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						case 3: // armor 4
						{
							if (player.get_gold() >= m_armor_objects_[armor_selection].m_sell_value)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char user_input2; // = 'n';
								std::cin >> user_input2;

								std::cout << '\n';

								switch (user_input2)
								{
									case 'y':
									case 'Y':
									{
										std::cout << "Here's your new " << m_armor_objects_[armor_selection].m_name << ". Thanks for your purchase." << '\n';

										player.equip_armor(m_armor_objects_[armor_selection]);
										player.buy(m_armor_objects_[armor_selection].m_sell_value);

										player.calculate_armor();


										std::cout << "You equip your new " << m_armor_objects_[armor_selection].m_name << '\n';

										exit_armor = true;

										break;
									}
									default:
									{
										std::cout << "No worries, maybe next time." << '\n';
										break;
									}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << '\n';
							}

							break;
						}
						default: // exit armor list
						{
							exit_armor = true;

							break;
						}
					}

				}

				break;
			}
			case 3: // buy potion
			{
				std::cout << "\nThe \"healing potion\" will cost 30 gold, do you still want it (y/n)? ";
				char potion_selection = 'n';
				std::cin >> potion_selection;

				switch (potion_selection)
				{
				case 'y':
				case 'Y':
				{
					const potion new_potion = add_potion(3, 8, 30); // low 3, high 8, price 30
					if (!player.add_new_potion(new_potion))
					{
						std::cout << '\n';
						std::cout << "I'm sorry but it looks like you already have too many potions," << '\n';
						std::cout << "these will be here if you need some once you used what you have." << '\n' << '\n';
					}
					else
					{
						player.buy(new_potion.m_sell_value);
						std::cout << "here you go, that's 1 healing potion." << '\n';
					}

					break;
				} // case 'y' || 'Y'
				default: // this option == no
				{
					std::cout << "no worries, maybe next time." << '\n';

					break;
				} // default
				}// end of switch
				
				break;
			}
			default: // leave the store
			{
				exit_store = true;

				////////////////////////////////////////////////////////////////////
				// DEBUG msg
				if (debug_log.enable_debug_messages)
				{
					std::cout << "debug message" << '\n';
					std::cout << "Weapon Bonus low: " << player.get_weapon_bonus(true) << '\n';
					std::cout << "Weapon Bonus high: " << player.get_weapon_bonus(false) << '\n';
					std::cout << '\n';

					std::cout << "original weapon low: " << player.get_original_weapon_value(true) << '\n';
					std::cout << "original weapon high: " << player.get_original_weapon_value(false) << '\n';
					std::cout << '\n';

				}

				break;
			}
		}
	}


}


store::store() = default;

store::~store() = default;