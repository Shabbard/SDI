#include <iostream>
#include "FilmProject.h"
#include "Material.h"
#include <numeric>

class View
{
private:
    /* data */
public:
    View(/* args */);
    ~View();
    void Main_Menu_Templates();
    void BM_Templates();
    void MM_Templates();
    void Edit_Templates();
    void CNP_Templates();
    void DisplayCurrentFilmProject(FilmProject*);
    void DisplayCrew(std::vector<Crew*>);
    void DisplayMaterial();
    void DisplayCreateNewMaterial();
    void LoadMatData(Material*, std::string);
    void Vector_Instructions();
    void Next_Back_Instructions();
    void value_error();
    
    void ShowStatusMeaning();
    void ShowInsertStatus();
    void ShowInsertTitle();
    void ShowInsertKeywords();
    void ShowInsertSummary();
    void ShowInsertGenre();
    void ShowInsertReleaseDate();
    void ShowInsertFilmingLocations();
    void ShowInsertRuntime();
    void ShowInsertLanguages();
    void ShowInsertWeeklyTicketSale();
    void DisplayCreateNewCrew();
    void ShowInsertCrewName();
    void ShowInsertCrewJob();
    void ShowInsertDataType();
    void ShowInsertEditGenre();
    void ShowInsertEditKeywords();
    void ShowInsertDescription();
    void ShowInsertVideoFormat();
    void ShowInsertAudioFormat();
    void ShowInsertRetailPrice();
    void ShowInsertSubtitles();
    void ShowInsertNumMaterials();
    void ShowInsertFilmIDs();
    void ShowRequestCrewID();
    void ShowVectorEdit(std::vector<std::string> strVec);
    void ShowDeleteGenre();
    void ShowDeleteKeywords();
    void ShowDeleteFilmingLocations();
    void ShowDeleteLanguages();
    void ShowEditDeleteCrew();
    void ShowDeleteCrew();
    void ShowSearchRequest();
    void ShowEnterProjectTitle();
    void ShowEnterActorName();
    void ShowEditDeleteMaterials();
    void ShowRequestMaterialID();
    void ShowDeleteMaterial();
    void ShowDeleteSubtitles();
    void ShowAddDeleteCrew();
    void DisplayFilmTitles(std::vector<std::string> films, std::string actorName);
    void New_data_report();
    void Total_Earnings_report(FilmProject*);
    void ReportsOptions();
    void ShowInsertFrameAspect();
    void ShowInsertPackaging();
    void ShowAddCrew();
    void ShowAddDeleteMaterial();
    void ShowAddMaterial();
    void DisplayEarningsReport();
};

