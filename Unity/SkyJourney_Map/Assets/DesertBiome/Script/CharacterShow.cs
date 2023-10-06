using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class CharacterShow : MonoBehaviour
{
    
    [SerializeField]
    private List<animations> animation;

    [SerializeField]
    private GameObject animButton;

    [SerializeField]
    private Transform scrollParent;

    private int index;

    private void Start()
    {
        Anim();
    }

    [System.Serializable]
    public class animations
    {
        public string name;

        public GameObject character;

        public Animator animator;

        public string[] animName;
    }

    public void LeftButton()
    {
        animation[index].character.SetActive(false);

        index--;

        if (index >= 0)
        {
            ShowCharacters();
        }
        else
        {
            index = animation.Count - 1;
            ShowCharacters();
        }
    }

    public void RightButton()
    {
        animation[index].character.SetActive(false);

        index++;

        if (index < animation.Count)
        {
            ShowCharacters();
        }
        else
        {
            index = 0;
            ShowCharacters();
        }
    }

    private void ShowCharacters()
    {
        animation[index].character.SetActive(true);
        animation[index].animator.Play(animation[index].animName.ToString());

        Anim();
    }

    private void Anim()
    {
        foreach (Transform btn in scrollParent)
        {
            Destroy(btn.gameObject);
        }

        for (int i = 0; i < animation[index].animName.Length; i++)
        {
            GameObject btn = Instantiate(animButton, scrollParent);

            btn.name = i.ToString();

            btn.transform.GetChild(0).GetComponent<Text>().text = animation[index].animName[i];

            btn.GetComponent<Button>().onClick.AddListener(() => ShowAnim());
        }

    }

    public void ShowAnim()
    {

        animation[index].animator.Play(EventSystem.current.currentSelectedGameObject.transform.GetChild(0).GetComponent<Text>().text);
        
    }
}
