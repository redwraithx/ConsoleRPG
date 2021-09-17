#include "Store.h"
#include "Armor.h"
#include "Weapon.h"
#include "Potion.h"

#include "Debug_Mode.h"

#include <iostream>


// Prototypes
void InitArmors(std::vector<Armor>& armorsContainer, std::string playerClass);
void InitWeapons(std::vector<Weapon>& weaponsContainer, std::string playerClass);
Potion addPotion(int low, int high, int price);


void Store::enter(Player& player)
{
	// init weapons
	InitWeapons(mWeaponObjects, player.getClass());
	// init armors
	InitArmors(mArmorObjects, player.getClass());



	////////////////////////////////////////////////////////////////////
	// DEBUG msg
	if (debugLog.enableDebugMessages)
	{
		std::cout << "debug message" << std::endl;
		std::cout << "Weapon Bonus low: " << player.getWeaponBonux(true) << std::endl;
		std::cout << "Weapon Bonus high: " << player.getWeaponBonux(false) << std::endl;
		std::cout << std::endl;

		std::cout << "original weapon low: " << player.getOriginalWeaponValue(true) << std::endl;
		std::cout << "original weapon high: " << player.getOriginalWeaponValue(false) << std::endl;
		std::cout << std::endl;
	}



	// player enters the store
	std::cout << "You enter a blacksmiths shop. You see weapons and armors laid about." << std::endl;

	// display the store goods
	bool exitStore = false;

	while (!exitStore)
	{
		
		if (player.getGold() < 30) // cheapest item to buy value is a heal potion
		{
			std::cout << "Hi Stranger... it seems you can't afford any of my stuff." << std::endl;
			std::cout << "Come back later with more gold." << std::endl << std::endl;

			exitStore = true;

			continue;
		}


		// store loop
		std::cout << std::endl << "Welcome to my Store." << std::endl;
		std::cout << "--------------------" << std::endl;



		std::cout << player.getName() << " you have " << player.getGold() << " gold coins." << std::endl;
		
		std::cout << std::endl << "1) Weapons list, 2) Armors List, 3) Buy a Potion, 4) leave the Store: ";
		int userInput = 1;
		std::cin >> userInput;



		switch (userInput)
		{
			case 1: // WEAPONS
			{
				bool exitWeapons = false;


				


				while (!exitWeapons)
				{
					std::cout << std::endl;


					// display the weapons for sale
					std::cout << "Weapons List" << std::endl;
					std::cout << "------------" << std::endl;

					int count = 0;
					for (int i = 0; i < mWeaponObjects.size(); i++)
					{
						std::cout << i << ") " << mWeaponObjects[i].mName << std::endl;

						count++;
					}

					std::cout << count << ") Exit Weapons List" << std::endl;
					std::cout << "Enter your selection: ";

					int weaponSelection = 0;
					std::cin >> weaponSelection;

					switch (weaponSelection)
					{
						case 0: // weapon 1
						{
							if (player.getGold() >= mWeaponObjects[weaponSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Heres your new " << mWeaponObjects[weaponSelection].mName << ". Thanks for your purchase." << std::endl;

									player.equipWeapon(mWeaponObjects[weaponSelection]);
									player.buy(mWeaponObjects[weaponSelection].mSellValue);

									player.calculateWeaponDamage();


									std::cout << "You equip your new " << mWeaponObjects[weaponSelection].mName << std::endl;

									exitWeapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << std::endl;
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						case 1: // weapon 2
						{
							if (player.getGold() >= mWeaponObjects[weaponSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Heres your new " << mWeaponObjects[weaponSelection].mName << ". Thanks for your purchase." << std::endl;

									player.equipWeapon(mWeaponObjects[weaponSelection]);
									player.buy(mWeaponObjects[weaponSelection].mSellValue);

									player.calculateWeaponDamage();


									std::cout << "You equip your new " << mWeaponObjects[weaponSelection].mName << std::endl;

									exitWeapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << std::endl;
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						case 2: // weapon 3
						{
							if (player.getGold() >= mWeaponObjects[weaponSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Heres your new " << mWeaponObjects[weaponSelection].mName << ". Thanks for your purchase." << std::endl;

									player.equipWeapon(mWeaponObjects[weaponSelection]);
									player.buy(mWeaponObjects[weaponSelection].mSellValue);

									player.calculateWeaponDamage();


									std::cout << "You equip your new " << mWeaponObjects[weaponSelection].mName << std::endl;

									exitWeapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << std::endl;
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						case 3: // weapon 4
						{
							if (player.getGold() >= mWeaponObjects[weaponSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Heres your new " << mWeaponObjects[weaponSelection].mName << ". Thanks for your purchase." << std::endl;

									player.equipWeapon(mWeaponObjects[weaponSelection]);
									player.buy(mWeaponObjects[weaponSelection].mSellValue);

									player.calculateWeaponDamage();


									std::cout << "You equip your new " << mWeaponObjects[weaponSelection].mName << std::endl;

									exitWeapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << std::endl;
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						case 4: // weapon 5
						{
							if (player.getGold() >= mWeaponObjects[weaponSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Heres your new " << mWeaponObjects[weaponSelection].mName << ". Thanks for your purchase." << std::endl;

									player.equipWeapon(mWeaponObjects[weaponSelection]);
									player.buy(mWeaponObjects[weaponSelection].mSellValue);

									player.calculateWeaponDamage();


									std::cout << "You equip your new " << mWeaponObjects[weaponSelection].mName << std::endl;

									exitWeapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << std::endl;
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						case 5: // weapon 6
						{
							if (player.getGold() >= mWeaponObjects[weaponSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
								case 'y':
								case 'Y':
								{
									std::cout << "Heres your new " << mWeaponObjects[weaponSelection].mName << ". Thanks for your purchase." << std::endl;

									player.equipWeapon(mWeaponObjects[weaponSelection]);
									player.buy(mWeaponObjects[weaponSelection].mSellValue);

									player.calculateWeaponDamage();


									std::cout << "You equip your new " << mWeaponObjects[weaponSelection].mName << std::endl;

									exitWeapons = true;

									break;
								}
								default:
								{
									std::cout << "No worries, maybe next time." << std::endl;
									break;
								}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						default: // exit weapons list
						{
							exitWeapons = true;

							break;
						}
					}

				}

				break;
			}
			case 2:  // ARMOR
			{
				bool exitArmor = false;

				while (!exitArmor)
				{
					std::cout << std::endl;


					// display the weapons for sale
					std::cout << "Armor List" << std::endl;
					std::cout << "------------" << std::endl;

					int count = 0;
					for (int i = 0; i < mArmorObjects.size(); i++)
					{
						std::cout << i << ") " << mArmorObjects[i].mName << std::endl;

						count++;
					}

					std::cout << count << ") Exit Armor List" << std::endl;
					std::cout << "Enter your selection: ";

					int armorSelection = 0;
					std::cin >> armorSelection;

					switch (armorSelection)
					{
						case 0: // armor 1
						{
							if (player.getGold() >= mArmorObjects[armorSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
									case 'y':
									case 'Y':
									{
										std::cout << "Heres your new " << mArmorObjects[armorSelection].mName << ". Thanks for your purchase." << std::endl;

										player.equipArmor(mArmorObjects[armorSelection]);
										player.buy(mArmorObjects[armorSelection].mSellValue);

										player.calculateArmor();


										std::cout << "You equip your new " << mArmorObjects[armorSelection].mName << std::endl;

										exitArmor = true;

										break;
									}
									default:
									{
										std::cout << "No worries, maybe next time." << std::endl;
										break;
									}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						case 1: // armor 2
						{
							if (player.getGold() >= mArmorObjects[armorSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
									case 'y':
									case 'Y':
									{
										std::cout << "Heres your new " << mArmorObjects[armorSelection].mName << ". Thanks for your purchase." << std::endl;

										player.equipArmor(mArmorObjects[armorSelection]);
										player.buy(mArmorObjects[armorSelection].mSellValue);

										player.calculateArmor();


										std::cout << "You equip your new " << mArmorObjects[armorSelection].mName << std::endl;

										exitArmor = true;

										break;
									}
									default:
									{
										std::cout << "No worries, maybe next time." << std::endl;
										break;
									}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						case 2: // armor 3
						{
							if (player.getGold() >= mArmorObjects[armorSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
									case 'y':
									case 'Y':
									{
										std::cout << "Heres your new " << mArmorObjects[armorSelection].mName << ". Thanks for your purchase." << std::endl;

										player.equipArmor(mArmorObjects[armorSelection]);
										player.buy(mArmorObjects[armorSelection].mSellValue);

										player.calculateArmor();


										std::cout << "You equip your new " << mArmorObjects[armorSelection].mName << std::endl;

										exitArmor = true;

										break;
									}
									default:
									{
										std::cout << "No worries, maybe next time." << std::endl;
										break;
									}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						case 3: // armor 4
						{
							if (player.getGold() >= mArmorObjects[armorSelection].mSellValue)
							{
								// do you want to buy it?
								std::cout << "Do you want to purchase this item? (y/n): ";
								char userInput = 'n';
								std::cin >> userInput;

								std::cout << std::endl;

								switch (userInput)
								{
									case 'y':
									case 'Y':
									{
										std::cout << "Heres your new " << mArmorObjects[armorSelection].mName << ". Thanks for your purchase." << std::endl;

										player.equipArmor(mArmorObjects[armorSelection]);
										player.buy(mArmorObjects[armorSelection].mSellValue);

										player.calculateArmor();


										std::cout << "You equip your new " << mArmorObjects[armorSelection].mName << std::endl;

										exitArmor = true;

										break;
									}
									default:
									{
										std::cout << "No worries, maybe next time." << std::endl;
										break;
									}
								}
							}
							else
							{
								std::cout << "I'm sorry you can't afford that item at this time. Maybe later." << std::endl;
							}

							break;
						}
						default: // exit armor list
						{
							exitArmor = true;

							break;
						}
					}

				}

				break;
			}
			case 3: // buy potion
			{
				std::cout << std::endl << "The \"healing potion\" will cost 30 gold, do you still want it (y/n)? ";
				char potionSelection = 'n';
				std::cin >> potionSelection;

				switch (potionSelection)
				{
				case 'y':
				case 'Y':
				{
					Potion newPotion = addPotion(3, 8, 30); // low 3, high 8, price 30
					if (!player.addNewPotion(newPotion))
					{
						std::cout << std::endl;
						std::cout << "I'm sorry but it looks like you already have too many potions," << std::endl;
						std::cout << "these will be here if you need some once you used what you have." << std::endl << std::endl;
					}
					else
					{
						player.buy(newPotion.mSellValue);
						std::cout << "here you go, thats 1 healing potion." << std::endl;
					}

					break;
				} // case 'y' || 'Y'
				default: // this option == no
				{
					std::cout << "no worries, maybe next time." << std::endl;

					break;
				} // default
				}// end of switch
				
				break;
			}
			default: // leave store
			{
				exitStore = true;

				////////////////////////////////////////////////////////////////////
				// DEBUG msg
				if (debugLog.enableDebugMessages)
				{
					std::cout << "debug message" << std::endl;
					std::cout << "Weapon Bonus low: " << player.getWeaponBonux(true) << std::endl;
					std::cout << "Weapon Bonus high: " << player.getWeaponBonux(false) << std::endl;
					std::cout << std::endl;

					std::cout << "original weapon low: " << player.getOriginalWeaponValue(true) << std::endl;
					std::cout << "original weapon high: " << player.getOriginalWeaponValue(false) << std::endl;
					std::cout << std::endl;

				}

				break;
			}
		}
	}


}


Store::Store()
{
	
}

Store::~Store()
{
}